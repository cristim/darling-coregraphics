/* Darling-specific: not upstreamable to GNUstep.

   OpalText is GNUstep code and uses GNUstep's memory-management and logging
   conveniences, which GNUstep declares as macros in NSObject.h and NSDebug.h.
   Darling's Foundation is Apple-shaped and does not have them, so those uses
   fall through to implicit function calls and fail at link, not at compile:

     ASSIGN, RETAIN, RELEASE, AUTORELEASE, NSWarnMLog

   This header supplies them with GNUstep's semantics. It exists because of
   what Darling's Foundation is, not because of anything wrong with Opal, so
   it must not be sent upstream. See DARLING-CHANGES.md. */

#ifndef DARLING_GNUSTEP_COMPAT_H
#define DARLING_GNUSTEP_COMPAT_H

#import <Foundation/NSObject.h>

#ifndef RETAIN
#define RETAIN(object)      [(object) retain]
#endif

#ifndef RELEASE
#define RELEASE(object)     [(object) release]
#endif

#ifndef AUTORELEASE
#define AUTORELEASE(object) [(object) autorelease]
#endif

/* Retains the new value before releasing the old one, so self-assignment and
   assigning a value owned only by the old one are both safe. */
#ifndef ASSIGN
#define ASSIGN(object, value) \
    do { \
        id __assign_new = (id) (value); \
        id __assign_old = (id) (object); \
        if (__assign_new != __assign_old) { \
            [__assign_new retain]; \
            (object) = (__typeof__(object)) __assign_new; \
            [__assign_old release]; \
        } \
    } while (0)
#endif

#ifndef NSWarnMLog
#define NSWarnMLog(format, ...) NSLog(@"WARNING: " format, ##__VA_ARGS__)
#endif

#endif /* DARLING_GNUSTEP_COMPAT_H */
