//
//  ViewController.m
//  OutParameters
//
//  Created by Franco Driansetti on 09/05/15.
//  Copyright (c) 2015 Franco Driansetti. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [ListOperation initialize];
    self.listOperationObj = [[ListOperation alloc]init];
}
- (IBAction)testCallMethod:(id)sender {
    NSString *output;
    [self.listOperationObj method1:&output];
    NSLog(@"Output: %@", output);
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
