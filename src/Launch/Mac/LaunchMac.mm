
#include <AppKit/AppKit.h>
#include <Foundation/Foundation.h>
#include <cstdlib>
#include <objc/objc.h>

// This part is heavily referencing the LaunchMac.cpp in the Unreal Engine

extern void RequestEngineExit();
extern bool IsEngineExitRequested();
extern void EngineSetWindow(void* Handle);
extern void EngineInitialize(const char* CmdLine);
extern bool EngineLoop();
extern int EngineShutdown();

@interface KumaWindowDelegate : NSObject <NSWindowDelegate>
{
}
@end

@implementation KumaWindowDelegate

- (void)windowWillClose:(NSNotification*)notification
{
    RequestEngineExit();
}

@end

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
    RequestEngineExit();
}

- (void)applicationWillFinishLaunching:(NSNotification*)notification
{
    NSMenu* MainMenu = [[NSMenu alloc] init];

    [NSApp setMainMenu:MainMenu];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
}

- (void)applicationDidFinishLaunching:(NSNotification*)Notification
{
    int WindowWidth = 800;
    int WindowHeight = 600;
    int WindowPositionX = 0;
    int WindowPositionY = 0;

    NSRect WindowRect =
        NSMakeRect(WindowPositionX, WindowPositionY, WindowWidth, WindowHeight);

    NSUInteger styleMask = NSWindowStyleMaskMiniaturizable |
                           NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |
                           NSWindowStyleMaskResizable;

    Window = [[NSWindow alloc] initWithContentRect:WindowRect
                                         styleMask:styleMask
                                           backing:NSBackingStoreBuffered
                                             defer:NO];

    [Window setTitle:@"Kuma Engine"];
    [Window setMinSize:NSMakeSize(400, 100)];
    [Window setRestorable:NO];
    [Window disableSnapshotRestoration];
    [Window setDelegate:[KumaWindowDelegate new]];

    const NSWindowCollectionBehavior Behavior =
        NSWindowCollectionBehaviorFullScreenPrimary |
        NSWindowCollectionBehaviorManaged;

    [Window setCollectionBehavior:Behavior];

    [Window makeKeyAndOrderFront:nil];

    EngineSetWindow(Window);
    [NSApp stop:nil];
}

- (bool
)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)Application
{
    return YES;
}

@end

void PollEvents()
{
    @autoreleasepool
    {
        while (true)
        {
            NSEvent* Event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                                untilDate:[NSDate distantPast]
                                                   inMode:NSDefaultRunLoopMode
                                                  dequeue:YES];

            if (Event == nil)
            {
                break;
            }

            [NSApp sendEvent:Event];
        }
    }
}

int main(int argc, char* argv[])
{
    @autoreleasepool
    {
        NSApplication* shared = [NSApplication sharedApplication];
        [NSApp setDelegate:[KumaAppDelegate new]];
        [NSApp run];
    }

    int EngineRunResult = 0;
    {
        EngineInitialize(nil);

        while (EngineLoop())
        {
            PollEvents();
        }

        EngineRunResult = EngineShutdown();
    }

    [NSApp terminate:nil];

    return EngineRunResult;
}
