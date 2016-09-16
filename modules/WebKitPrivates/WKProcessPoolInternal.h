/*
 * https://github.com/WebKit/webkit/blob/67985c34ffc405f69995e8a35f9c38618625c403/Source/WebKit2/UIProcess/API/Cocoa/WKProcessPoolInternal.h
 * Copyright (C) 2014 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#import "WKProcessPoolPrivate.h"

#if WK_API_ENABLED

//#import "WebProcessPool.h"

#if TARGET_OS_IPHONE
@class WKGeolocationProviderIOS;
#endif

namespace WebKit {

inline WKProcessPool *wrapper(WebProcessPool& processPool)
{
    ASSERT([processPool.wrapper() isKindOfClass:[WKProcessPool class]]);
    return (WKProcessPool *)processPool.wrapper();
}

}

#ifdef __cplusplus
#import "WKObject.h"
@interface WKProcessPool () { <WKObject> {
@package
    API::ObjectStorage<WebKit::WebProcessPool> _processPool;
    // https://github.com/WebKit/webkit/blob/72068f140de6e48078749591a06a81f24a4034c4/Source/WebKit2/UIProcess/WebProcessPool.h
    // https://github.com/WebKit/webkit/blob/72068f140de6e48078749591a06a81f24a4034c4/Source/WebKit2/UIProcess/WebProcessPool.cpp

}
#endif

#if TARGET_OS_IPHONE
@property(readonly) WKGeolocationProviderIOS *_geolocationProvider;
#endif
@end

#endif // WK_API_ENABLED
