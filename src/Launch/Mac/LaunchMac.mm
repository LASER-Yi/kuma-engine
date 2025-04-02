
#include <AppKit.h>
#include <AppKit/AppKit.h>
#include <Foundation/Foundation.h>
#include <cstdlib>

// This part is heavily referencing the LaunchMac.cpp in the Unreal Engine

extern void RequestEngineExit();
extern bool IsEngineExitRequested();

extern int GuardedMain(const char*);
extern void* GWindow;

static NSThread* GGameThread = nil;
static int GGuardedMainErrorLevel = 0;

const NSUInteger GameThreadStackSize = 128 * 1024 * 1024;

void RunGameThread(id Target, SEL Selector)
{
    @autoreleasepool
    {
        [[NSProcessInfo processInfo] disableSuddenTermination];

        // Create a separate game thread and set its stack size to be the same
        // as the main thread.
        NSThread* GameThread = [[NSThread alloc] initWithTarget:Target
                                                       selector:Selector
                                                         object:nil];

        [GameThread setStackSize:GameThreadStackSize];
        [GameThread start];

        GGameThread = GameThread;
    }
}

@interface KumaAppDelegate : NSObject <NSApplicationDelegate>
{
    NSWindow* Window;
}
@end

@implementation KumaAppDelegate

- (NSApplicationTerminateReply
)applicationShouldTerminate:(NSApplication*)Sender;
{
    if (IsEngineExitRequested() == false)
    {
        // TODO: We will need to call this in the game thread
        RequestEngineExit();
        return NSTerminateLater;
    }
    else
    {

        return NSTerminateNow;
    }
}

- (void)applicationWillTerminate:(NSNotification*)Notification
{
}

- (void)applicationDidFinishLaunching:(NSNotification*)Notification
{

    int WindowWidth = 800;
    int WindowHeight = 600;
    int WindowPositionX = 0;
    int WindowPositionY = 0;

    NSRect WindowRect =
        NSMakeRect(WindowPositionX, WindowPositionY, WindowWidth, WindowHeight);

    Window = [[NSWindow alloc] initWithContentRect:WindowRect
                                         styleMask:NSWindowStyleMaskTitled |
                                                   NSWindowStyleMaskResizable |
                                                   NSWindowStyleMaskClosable
                                           backing:NSBackingStoreBuffered
                                             defer:NO];

    [Window setTitle:@"Kuma Engine"];
    [Window setMinSize:NSMakeSize(400, 100)];
    [Window setRestorable:NO];
    [Window disableSnapshotRestoration];

    [Window makeKeyAndOrderFront:nil];

    GWindow = Window;
    RunGameThread(self, @selector(runGameThread:));
}

- (bool
)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)Application
{
    return true;
}

- (void)runGameThread:(id)Arg
{
    GGuardedMainErrorLevel = GuardedMain(nil);

    if (GGuardedMainErrorLevel == 0)
    {
        dispatch_async(dispatch_get_main_queue(), ^{
          [NSApp terminate:nil];
        });
    }
    else
    {
        _Exit(GGuardedMainErrorLevel);
    }
}

@end

int main(int argc, char* argv[])
{
    @autoreleasepool
    {
        NSApplication* shared = [NSApplication sharedApplication];
        [shared setDelegate:[KumaAppDelegate new]];
        [shared run];
    }

    return GGuardedMainErrorLevel;
}
