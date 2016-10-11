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
    
protected:
    void  UpdateDetector(uint32_t rtp_timestamp, int64_t receive_timestamp, size_t packet_size);
    
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
