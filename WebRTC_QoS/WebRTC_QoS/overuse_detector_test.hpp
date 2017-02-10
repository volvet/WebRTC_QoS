//
//  overuse_detector_test.hpp
//  WebRTC_QoS
//
//  Created by Volvet Zhang on 16/10/11.
//  Copyright © 2016年 volvet. All rights reserved.
//

#ifndef overuse_detector_test_hpp
#define overuse_detector_test_hpp

#include <stdio.h>
#include "Random.hpp"
#include "overuse_detector.hpp"
#include "inter_arrival.hpp"

namespace webrtc {

class OveruseDetectorTest
{
public:
    OveruseDetectorTest();
    virtual ~OveruseDetectorTest();
    
    
    void  GaussionRandom();
    void  SimpleNonOveruse30fps();
    void  SimpleNonOveruseWithReceiveVariance();
    void  SimpleNonOveruseWithRtpTimevariance();
    void  SimpleOveruse2000kbit30fps();
    
protected:
    void  UpdateDetector(uint32_t rtp_timestamp, int64_t receive_timestamp, size_t packet_size);
    int   Run100000Samples(int packets_per_frame, size_t packet_size, int mean_ms, int standard_deviation_ms);
    int   RunUntilOveruse(int packets_per_frame, size_t packet_size, int mean_ms, int standard_deviation_ms, int drift_per_frame_ms);
    
private:
    int64_t      mNow;
    int64_t      mReceiveTimestamp;
    uint32_t     mRTPTimestamp;
    Random       mRandom;
    OveruseDetector  * m_pOveruseDetector;
    OveruseEstimator * m_pOveruseEstimator;
    InterArrival     * m_pInterArrival;
};

}

#endif /* overuse_detector_test_hpp */
