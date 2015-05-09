#pragma mark - Logging section

typedef enum {
    LL_ERROR=1,
    LL_WARNING=2,
    LL_INFO=4,
    LL_DEBUG=8,
    LL_VERBOSE=16,
    LL_VERBOSEFUNC=32
} CSLogLevel;

//each .m should initialize a static logLevel variable defining the requered CSLOG_LEVEL_FLAG:
//e.g.:
//static CSLogLevel logLevel = CSLOG_LEVEL_INFO;

//each method should begin and end with LOGFSTART and LOGFEND in order to trace the method life-cycle
//use LOGE(...) to trace error messages
//use LOGW(...) to trace error/warning messages
//use LOGI(...) to trace error/warning/info messages
//use LOGD(...) to trace error/warning/info/debug messages
//use LOGV(...) to trace error/warning/info/debug/verbose messages

#define CSLOG_LEVEL_OFF           0
#define CSLOG_LEVEL_ERROR         LL_ERROR
#define CSLOG_LEVEL_WARNING       (LL_ERROR|LL_WARNING)
#define CSLOG_LEVEL_INFO          (LL_ERROR|LL_WARNING|LL_INFO)
#define CSLOG_LEVEL_DEBUG         (LL_ERROR|LL_WARNING|LL_INFO|LL_DEBUG)
#define CSLOG_LEVEL_VERBOSE       (LL_ERROR|LL_WARNING|LL_INFO|LL_DEBUG|LL_VERBOSE)
#define CSLOG_LEVEL_VERBOSEFUNC   (LL_ERROR|LL_WARNING|LL_INFO|LL_DEBUG|LL_VERBOSE|LL_VERBOSEFUNC)

//logs error messages
#define LOGE(fmt, ...)  if((logLevel & LL_ERROR) == LL_ERROR) {                                     \
                            NSLog((@"%s [%d] " fmt),__PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);  \
                        }
//logs debug messages
#define LOGD(fmt, ...)  if((logLevel & LL_DEBUG) == LL_DEBUG) {                                     \
                            NSLog((@"%s [%d] " fmt),__PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);  \
                        }
//logs info messages
#define LOGI(fmt, ...)  if((logLevel & LL_INFO) == LL_INFO) {                                       \
                            NSLog((@"%s [%d] " fmt),__PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);  \
                        }
//logs warning messages
#define LOGW(fmt, ...)  if((logLevel & LL_WARNING) == LL_WARNING) {                                 \
                            NSLog((@"%s [%d] " fmt),__PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);  \
                        }
//logs verbose messages
#define LOGV(fmt, ...)  if((logLevel & LL_VERBOSE) == LL_VERBOSE) {                                 \
                            NSLog((@"%s [%d] " fmt),__PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);  \
                        }
//logs verboseFunction messages
#define LOGVF(fmt, ...) if((logLevel & LL_VERBOSEFUNC) == LL_VERBOSEFUNC) {                         \
                            NSLog((@"%s [%d] " fmt),__PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);  \
                        }

#define LOGFSTART   LOGVF(@"START");    //logs the start of a method
#define LOGFEND     LOGVF(@"END");      //logs the end of a method



#pragma mark - Block management

#define WEAK        __weak typeof(self) weakSelf = self;
//call STRONG inside blocks and use 'strongSelf' instead of 'self' to avoid retain cycles
#define STRONG      typeof(self) strongSelf = weakSelf; if(!strongSelf) return;

//e.g.:

//__weak UIViewController *weakSelf = self;
//self.onSomething = ^{
//    __strong UIViewController *strongSelf = weakSelf;
//    if(strongSelf) {
//        [strongSelf doSomethingElse];
//        strongSelf = nil;
//    }
//};

//becomes:

//WEAK
//self.onSomething = ^{
//    STRONG
//    [strongSelf doSomethingElse];
//};


#pragma mark - Notification shortcuts

#define ADD_OBSERVER(notification,sel)  [[NSNotificationCenter defaultCenter] addObserver:self  \
                                                selector:@selector(sel)                         \
                                                name:notification                               \
                                                object:nil]
//e.g.:
//ADD_OBSERVER(UIDeviceOrientationDidChangeNotification,_onOrientationChanged:);

#define REMOVE_OBSERVER(notification)   [[NSNotificationCenter defaultCenter] removeObserver:self \
                                                name:notification                                 \
                                                object:nil]



#pragma mark - Errors

#define ERROR(domainName,errorCode,description)     [NSError errorWithDomain:domainName             \
                                                        code:errorCode                              \
                                                    userInfo:@{                                     \
                                                        NSLocalizedDescriptionKey :                 \
                                                        description                                 \
                                                }]
//e.g.:
//NSError *error = ERROR(@"MyApp",-1001,@"E' avvenuto un errore imprevisto in %@",self);


#pragma mark - AppDelegate

#define APP_DELEGATE        ((AppDelegate*)[UIApplication sharedApplication].delegate)



#pragma mark - dispatch

#define DT(time)            dispatch_time(DISPATCH_TIME_NOW, (int64_t)(time * NSEC_PER_SEC))