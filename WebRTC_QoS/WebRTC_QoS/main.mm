//
//  main.m
//  WebRTC_QoS
//
//  Created by Volvet Zhang on 16/10/9.
//  Copyright © 2016年 volvet. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "overuse_detector_test.hpp"

using namespace webrtc;

int QoSTest()
{
    NSLog(@"WebRTC QoS Test");
    OveruseDetectorTest  overuseDetectorTest;
    
    NSLog(@"GaussionRandom");
    overuseDetectorTest.GaussionRandom();
    
    NSLog(@"SimpleNonOveruse");
    overuseDetectorTest.SimpleNonOveruse30fps();
    
    NSLog(@"SimpleNonOveruseWithReceiveVariance");
    overuseDetectorTest.SimpleNonOveruseWithReceiveVariance();
    
    NSLog(@"SimpleNonOveruseWithRtpTimevariance");
    overuseDetectorTest.SimpleNonOveruseWithRtpTimevariance();
    
    NSLog(@"SimpleOveruse2000kbit30fps");
    overuseDetectorTest.SimpleOveruse2000kbit30fps();
    
    NSLog(@"Test Done");
    return 0;
}



int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        QoSTest();
    }
    return 0;
}
