@import WebKit;
// https://github.com/WebKit/webkit/blob/master/Source/WebKit/UIProcess/API/Cocoa/WKWebViewPrivate.h
// https://github.com/WebKit/webkit/blob/master/Source/WebKit/UIProcess/Cocoa/WebViewImpl.h
// https://github.com/WebKit/webkit/blob/master/Source/WebCore/page/Settings.in

#import "_WKLayoutMode.h"
#import "_WKFindOptions.h"
#import "_WKInputDelegate.h"

typedef NS_ENUM(NSInteger, _WKPaginationMode) {
    _WKPaginationModeUnpaginated,
    _WKPaginationModeLeftToRight,
    _WKPaginationModeRightToLeft,
    _WKPaginationModeTopToBottom,
    _WKPaginationModeBottomToTop,
} WK_API_AVAILABLE(macosx(10.10), ios(8.0));

typedef NS_ENUM(NSInteger, _WKImmediateActionType) {
    _WKImmediateActionNone,
    _WKImmediateActionLinkPreview,
    _WKImmediateActionDataDetectedItem,
    _WKImmediateActionLookupText,
    _WKImmediateActionMailtoLink,
    _WKImmediateActionTelLink
} WK_API_AVAILABLE(macosx(10.12));

typedef NS_OPTIONS(NSInteger, _WKMediaCaptureState) {
    _WKMediaCaptureStateNone = 0,
    _WKMediaCaptureStateActiveMicrophone = 1 << 0,
    _WKMediaCaptureStateActiveCamera = 1 << 1,
    _WKMediaCaptureStateMutedMicrophone = 1 << 2,
    _WKMediaCaptureStateMutedCamera = 1 << 3,
} WK_API_AVAILABLE(macosx(10.13), ios(11.0));

typedef NS_OPTIONS(NSInteger, _WKMediaMutedState) {
    _WKMediaNoneMuted = 0,
    _WKMediaAudioMuted = 1 << 0,
    _WKMediaCaptureDevicesMuted = 1 << 1,
} WK_API_AVAILABLE(macosx(10.13), ios(11.0));

typedef NS_OPTIONS(NSUInteger, _WKCaptureDevices) {
    _WKCaptureDeviceMicrophone = 1 << 0,
    _WKCaptureDeviceCamera = 1 << 1,
    _WKCaptureDeviceDisplay = 1 << 2,
} WK_API_AVAILABLE(macosx(10.13), ios(11.0));

#import "WKBrowsingContextHandle.h"
@class WKBrowsingContextHandle;
@class _WKApplicationManifest;
@class _WKIconLoadingDelegate;
@class _WKThumbnailView;
@class _WKFrameHandle;

@protocol _WKFindDelegate;
@protocol _WKDiagnosticLoggingDelegate;
//@protocol _WKInputDelegate;
@protocol WKHistoryDelegatePrivate;
@protocol _WKIconLoadingDelegate;

@interface WKWebView (Privates)

@property (nonatomic, readonly) WKBrowsingContextHandle *_handle;

- (WKPageRef)_pageForTesting;

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
//@property (nonatomic, readonly) _WKWebViewPrintFormatter *_webViewPrintFormatter;
//@property (nonatomic, getter=_allowsLinkPreview, setter=_setAllowsLinkPreview:) BOOL _allowsLinkPreview
@property (nonatomic, setter=_setBackgroundExtendsBeyondPage:) BOOL _backgroundExtendsBeyondPage;
- (UIView *)_viewForFindUI;
@property (nonatomic, readonly) CGFloat _viewportMetaTagWidth; // negative if tag undefined
@property (nonatomic, readonly) _WKWebViewPrintFormatter *_webViewPrintFormatter;
#else
@property (readonly) NSColor *_pageExtendedBackgroundColor;
@property (nonatomic, setter=_setTopContentInset:) CGFloat _topContentInset;
@property (nonatomic, setter=_setAutomaticallyAdjustsContentInsets:) BOOL _automaticallyAdjustsContentInsets;

// https://bugs.webkit.org/show_bug.cgi?id=177022
@property (nonatomic, readonly) WKPageRef _pageRefForTransitionToWKWebView WK_API_AVAILABLE(macos(10.13.4));

- (void)_setFrame:(NSRect)rect andScrollBy:(NSSize)offset WK_API_AVAILABLE(macosx(10.13.4));

- (void)_gestureEventWasNotHandledByWebCore:(NSEvent *)event WK_API_AVAILABLE(macosx(10.13.4));
- (void)_setCustomSwipeViews:(NSArray *)customSwipeViews WK_API_AVAILABLE(macosx(10.13.4));
- (void)_setCustomSwipeViewsTopContentInset:(float)topContentInset WK_API_AVAILABLE(macosx(10.13.4));
- (NSView *)_fullScreenPlaceholderView WK_API_AVAILABLE(macosx(10.13.4));
- (NSWindow *)_fullScreenWindow WK_API_AVAILABLE(macosx(10.13.4));

@property (nonatomic, readonly) BOOL _hasActiveVideoForControlsManager WK_API_AVAILABLE(macosx(10.12));
- (void)_requestControlledElementID WK_API_AVAILABLE(macosx(10.12.3));
- (void)_handleControlledElementIDResponse:(NSString *)identifier WK_API_AVAILABLE(macosx(10.12.3));
- (void)_handleAcceptedCandidate:(NSTextCheckingResult *)candidate WK_API_AVAILABLE(macosx(10.12.3));
- (void)_didHandleAcceptedCandidate WK_API_AVAILABLE(macosx(10.12.3));
- (void)_forceRequestCandidates WK_API_AVAILABLE(macosx(10.12.3));
- (void)_didUpdateCandidateListVisibility:(BOOL)visible WK_API_AVAILABLE(macosx(10.12.3));
@property (nonatomic, readonly) BOOL _shouldRequestCandidates WK_API_AVAILABLE(macosx(10.12.3));
- (void)_insertText:(id)string replacementRange:(NSRange)replacementRange WK_API_AVAILABLE(macosx(10.12.3));
- (NSRect)_candidateRect WK_API_AVAILABLE(macosx(10.13));
@property (nonatomic, readwrite, setter=_setUseSystemAppearance:) BOOL _useSystemAppearance WK_API_AVAILABLE(macosx(WK_MAC_TBA));

- (void)_setHeaderBannerHeight:(int)height WK_API_AVAILABLE(macosx(10.12.3));
- (void)_setFooterBannerHeight:(int)height WK_API_AVAILABLE(macosx(10.12.3));

// TODO: make Status Bar from NSTrackingArea's tooltips
// https://developer.apple.com/library/mac/documentation/Cocoa/Conceptual/EventOverview/TrackingAreaObjects/TrackingAreaObjects.html#//apple_ref/doc/uid/10000060i-CH8-SW1
- (NSString *)view:(NSView *)view stringForToolTip:(NSToolTipTag)tag point:(NSPoint)point userData:(void *)data;
- (NSView *)documentContainerView;
#endif

@property (nonatomic, setter=_setLayoutMode:) _WKLayoutMode _layoutMode;
@property (nonatomic, setter=_setViewScale:) CGFloat _viewScale;

// hard-renamed to ^background in 11/2015. only pre-macOS with no STP will respond to ^transparentBackground.
// https://github.com/WebKit/webkit/commit/6cbd5051e809407615b2fd903dacc8c14bbd69eb =>
// https://trac.webkit.org/browser/webkit/tags/Safari-602.1.11/Source/WebKit2/ChangeLog
@property (nonatomic, setter=_setDrawsBackground:) BOOL _drawsBackground WK_API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, setter=_setDrawsTransparentBackground:) BOOL _drawsTransparentBackground; // DEPRECATED!

// https://bugs.webkit.org/show_bug.cgi?id=151276 ChangeLog-2015-11-21
- (NSPrintOperation *)_printOperationWithPrintInfo:(NSPrintInfo *)printInfo; // prints top frame
- (NSPrintOperation *)_printOperationWithPrintInfo:(NSPrintInfo *)printInfo forFrame:(_WKFrameHandle *)frameHandle WK_API_AVAILABLE(macosx(10.12), ios(10.0));

-(void)_close;

@property (nonatomic, readonly) BOOL _networkRequestsInProgress;
@property (nonatomic, getter=_isEditable, setter=_setEditable:) BOOL _editable WK_API_AVAILABLE(macosx(10.11), ios(9.0));
@property (nonatomic, setter=_setAddsVisitedLinks:) BOOL _addsVisitedLinks;
@property (nonatomic, setter=_setAllowsRemoteInspection:) BOOL _allowsRemoteInspection;
@property (nonatomic, copy, setter=_setRemoteInspectionNameOverride:) NSString *_remoteInspectionNameOverride WK2_AVAILABLE(WK_MAC_TBA, WK_IOS_TBA);
@property (copy, setter=_setCustomUserAgent:) NSString *_customUserAgent;
@property (copy, setter=_setApplicationNameForUserAgent:) NSString *_applicationNameForUserAgent;
@property (nonatomic, readonly) NSString *_userAgent WK_API_AVAILABLE(macosx(10.11), ios(9.0));
@property (nonatomic, readonly) BOOL _supportsTextZoom;
@property (nonatomic, setter=_setTextZoomFactor:) double _textZoomFactor;
@property (nonatomic, setter=_setPageZoomFactor:) double _pageZoomFactor;
@property (nonatomic, readonly, getter=_isDisplayingStandaloneImageDocument) BOOL _displayingStandaloneImageDocument;
@property (nonatomic, setter=_setPaginationMode:) _WKPaginationMode _paginationMode;
@property (nonatomic, setter=_setPaginationBehavesLikeColumns:) BOOL _paginationBehavesLikeColumns;
@property (nonatomic, setter=_setPageLength:) CGFloat _pageLength;
@property (nonatomic, setter=_setGapBetweenPages:) CGFloat _gapBetweenPages;
- (void)_loadAlternateHTMLString:(NSString *)string baseURL:(NSURL *)baseURL forUnreachableURL:(NSURL *)unreachableURL;
- (void)_getMainResourceDataWithCompletionHandler:(void (^)(NSData *, NSError *))completionHandler;
- (void)_getWebArchiveDataWithCompletionHandler:(void (^)(NSData *, NSError *))completionHandler;
- (void)_getContentsAsStringWithCompletionHandler:(void (^)(NSString *, NSError *))completionHandler WK_API_AVAILABLE(macosx(10.13), ios(11.0));
- (void)_getApplicationManifestWithCompletionHandler:(void (^)(_WKApplicationManifest *))completionHandler WK_API_AVAILABLE(macosx(WK_MAC_TBA), ios(WK_IOS_TBA));
@property (nonatomic, readonly) NSURL *_unreachableURL;
@property (nonatomic, readonly) NSURL *_committedURL;
@property (nonatomic, readonly) NSString *_MIMEType;

@property (nonatomic, weak, setter=_setDiagnosticLoggingDelegate:) id <_WKDiagnosticLoggingDelegate> _diagnosticLoggingDelegate WK_API_AVAILABLE(macosx(10.11), ios(9.0));
//https://github.com/WebKit/webkit/blob/master/Source/WebKit/UIProcess/API/Cocoa/_WKFormDelegate.h
//@property (nonatomic, weak, setter=_setFormDelegate:) id <_WKFormDelegate> _formDelegate;

@property (nonatomic, weak, setter=_setFindDelegate:) id <_WKFindDelegate> _findDelegate;
- (void)_findString:(NSString *)string options:(_WKFindOptions)options maxCount:(NSUInteger)maxCount;
- (void)_countStringMatches:(NSString *)string options:(_WKFindOptions)options maxCount:(NSUInteger)maxCount;
- (void)_hideFindUI;

@property (nonatomic, weak, setter=_setInputDelegate:) id <_WKInputDelegate> _inputDelegate WK_API_AVAILABLE(macosx(10.12), ios(10.0));

@property (nonatomic, weak, setter=_setHistoryDelegate:) id <WKHistoryDelegatePrivate> _historyDelegate;

// Icon delegate https://github.com/WebKit/webkit/commit/583510ef68c8aa56558c17263791b5cd8f762f99
@property (nonatomic, weak, setter=_setIconLoadingDelegate:) id <_WKIconLoadingDelegate> _iconLoadingDelegate;

@property (strong, nonatomic, setter=_setInspectorAttachmentView:) NSView *_inspectorAttachmentView WK_API_AVAILABLE(macosx(10.13.4));

// https://github.com/WebKit/webkit/commit/cabc571fb1a8b5d599592662d4823af181f5dab3#diff-8e23aa6fa7b7953093696656facbb583
@property (nonatomic, setter=_setThumbnailView:) _WKThumbnailView *_thumbnailView WK_API_AVAILABLE(macosx(10.13.4));
@property (nonatomic, setter=_setIgnoresAllEvents:) BOOL _ignoresAllEvents WK_API_AVAILABLE(macosx(10.13.4));

@property (nonatomic, setter=_setScrollPerformanceDataCollectionEnabled:) BOOL _scrollPerformanceDataCollectionEnabled WK_API_AVAILABLE(macosx(10.11), ios(9.0));
@property (nonatomic, readonly) NSArray *_scrollPerformanceData WK_API_AVAILABLE(macosx(10.11), ios(9.0));

- (void)_saveBackForwardSnapshotForItem:(WKBackForwardListItem *)item WK_API_AVAILABLE(macosx(10.11), ios(9.0));

@property (nonatomic, getter=_allowsMediaDocumentInlinePlayback, setter=_setAllowsMediaDocumentInlinePlayback:) BOOL _allowsMediaDocumentInlinePlayback;

@property (nonatomic, readonly) BOOL _webProcessIsResponsive WK_API_AVAILABLE(macosx(10.12), ios(10.0));

//@property (nonatomic, setter=_setFullscreenDelegate:) id<_WKFullscreenDelegate> _fullscreenDelegate WK_API_AVAILABLE(macosx(10.13), ios(11.0));
@property (nonatomic, readonly) BOOL _isInFullscreen WK_API_AVAILABLE(macosx(10.12.3));

- (void)_muteMediaCapture WK_API_AVAILABLE(macosx(10.13), ios(11.0));
- (void)_setPageMuted:(_WKMediaMutedState)mutedState WK_API_AVAILABLE(macosx(10.13), ios(11.0));

@property (nonatomic, setter=_setMediaCaptureEnabled:) BOOL _mediaCaptureEnabled WK_API_AVAILABLE(macosx(10.13), ios(11.0));

//@property (nonatomic, readonly) _WKInspector *_inspector WK_API_AVAILABLE(macosx(WK_MAC_TBA), ios(WK_IOS_TBA));
@property (nonatomic, readonly) _WKFrameHandle *_mainFrame WK_API_AVAILABLE(macosx(WK_MAC_TBA), ios(WK_IOS_TBA));

@end

// https://github.com/WebKit/webkit/commit/1e291e88d96caa8e5421f81bd570e90b1af02ff4
#if TARGET_OS_OSX
@interface WKWebView (WKNSTextFinderClient) <NSTextFinderClient>
@end

@interface WKTextFinderMatch : NSObject <NSTextFinderAsynchronousDocumentFindMatch>
@property (nonatomic, readonly) unsigned index;
@end

@interface WKWebView (NSTextFinderSupport)
- (void)findMatchesForString:(NSString *)targetString relativeToMatch:(id <NSTextFinderAsynchronousDocumentFindMatch>)relativeMatch findOptions:(NSTextFinderAsynchronousDocumentFindOptions)findOptions maxResults:(NSUInteger)maxResults resultCollector:(void (^)(NSArray *matches, BOOL didWrap))resultCollector;
- (void)getSelectedText:(void (^)(NSString *selectedTextString))completionHandler;
- (void)selectFindMatch:(id <NSTextFinderAsynchronousDocumentFindMatch>)findMatch completionHandler:(void (^)(void))completionHandler;
@end
#endif

// CPU limit!!
// https://github.com/WebKit/webkit/commit/7cb2c970ac18d8ea58d95236ef6897feb7f7fb01#diff-8e23aa6fa7b7953093696656facbb583

// [WKWebView _pageRefForTransitionToWKWebView]
// https://github.com/WebKit/webkit/commit/77f18c8949dad58b43e81f35d1b861a0f28a0efa#diff-8e23aa6fa7b7953093696656facbb583

// moar from WebViewImpl !!
// https://github.com/WebKit/webkit/commit/cfe92b4e265636c1396c7c7ed188cc51b78582ca#diff-8e23aa6fa7b7953093696656facbb583
// https://github.com/WebKit/webkit/commit/dcb4f6fd0815005282c92da91b5f26b12083821d#diff-8e23aa6fa7b7953093696656facbb583
