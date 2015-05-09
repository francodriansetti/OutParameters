//
//  ListOperation.m
//  OutParameters
//
//  Created by Franco Driansetti on 09/05/15.
//  Copyright (c) 2015 Franco Driansetti. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ListOperation.h"
#import "Macros.h"
#import <UIKit/UIKit.h>
#import "string"

#define MAX_OPERATIONS 10
//define a log-level
static int logLevel = CSLOG_LEVEL_INFO;
@interface ListOperation ()
// Tail used to synchronize the methods
@property NSOperationQueue *queue;
@end

#pragma mark - Public methods

@implementation ListOperation

- (id)init {
    self = [super init];
    if(self) {
        _queue = [NSOperationQueue new];
        if(_queue) {
            [_queue setMaxConcurrentOperationCount:1];
        }else {
            NSLog(@"TokenMgr creation failed: error creating operation queue");
            self = nil;
        }
    }
    return self;
}

-(void)method1:(NSString *__autoreleasing *)output{
    LOGFSTART
    if([self _isQueueFull] == FALSE) {
        WEAK
        NSBlockOperation *operation = [NSBlockOperation blockOperationWithBlock:^{
            STRONG
            [strongSelf _method1:output];
        }];
        [self.queue addOperation:operation];
        [operation waitUntilFinished];
    }
    else {
        LOGE(@"TokenMgr's queue is full, aborting operation");
    }
    LOGFEND
}

#pragma mark - private methods

-(void)_method1:(NSString *__autoreleasing *)output{
    std::string testString = "try put string";
    *output = [NSString stringWithUTF8String:testString.c_str()];
}

- (BOOL) _isQueueFull {
    return self.queue.operationCount > MAX_OPERATIONS;
}

@end