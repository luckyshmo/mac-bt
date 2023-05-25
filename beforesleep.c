#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
 
#include <mach/mach_port.h>
#include <mach/mach_interface.h>
#include <mach/mach_init.h>
 
#include <IOKit/pwr_mgt/IOPMLib.h>
#include <IOKit/IOMessage.h>
 
io_connect_t  root_port; // a reference to the Root Power Domain IOService
 
void
MySleepCallBack( void * refCon, io_service_t service, natural_t messageType, void * messageArgument )
{
    switch ( messageType )
    {
 
        
        case kIOMessageCanSystemSleep:
            break;
 
        case kIOMessageSystemWillSleep:
            // add want you want here. and fix the path
            system("/opt/homebrew/bin/blueutil --disconnect 94:DB:56:DE:BE:60");
            system("pmset sleepnow"); 
            break;
 
        case kIOMessageSystemWillPowerOn:
            //System has started the wake up process...
            break;
 
        case kIOMessageSystemHasPoweredOn:
            //System has finished waking up...
        break;
 
        default:
            break;
 
    }
}
 
 
int main( int argc, char **argv )
{
    
    // notification port allocated by IORegisterForSystemPower
    IONotificationPortRef  notifyPortRef;
 
    // notifier object, used to deregister later
    io_object_t            notifierObject;
   // this parameter is passed to the callback
    void*                  refCon;
 
    // register to receive system sleep notifications
 
    root_port = IORegisterForSystemPower( refCon, &notifyPortRef, MySleepCallBack, &notifierObject );
    if ( root_port == 0 )
    {
        printf("IORegisterForSystemPower failed\n");
        return 1;
    }
 
    // add the notification port to the application runloop
    CFRunLoopAddSource( CFRunLoopGetCurrent(),
            IONotificationPortGetRunLoopSource(notifyPortRef), kCFRunLoopCommonModes );
 
    /* Start the run loop to receive sleep notifications. Don't call CFRunLoopRun if this code
        is running on the main thread of a Cocoa or Carbon application. Cocoa and Carbon
        manage the main thread's run loop for you as part of their event handling
        mechanisms.
    */
    CFRunLoopRun();
 
    //Not reached, CFRunLoopRun doesn't return in this case.
    return (0);
}
