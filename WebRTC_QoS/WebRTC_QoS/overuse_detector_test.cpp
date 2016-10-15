//
//  overuse_detector_test.cpp
//  WebRTC_QoS
//
//  Created by Volvet Zhang on 16/10/11.
//  Copyright © 2016年 volvet. All rights reserved.
//

#include <assert.h>
#include <string>
#include "overuse_detector_test.hpp"

using namespace std;

namespace webrtc {

    const double KRTPTimestampToMS = 1.0/90.0;
    
    std::string BandwdithState2String(BandwidthUsage state)
    {
        if( state == kBwNormal ){
            return "BW Normal";
        } else if ( state == kBwOverusing ) {
            return "BW Overusing";
        }
        return "BW Underusning";
    }
    
    OveruseDetectorTest::OveruseDetectorTest() : mRandom(123456789)
    {
        OverUseDetectorOptions  options;
        m_pInterArrival = new InterArrival(5*90, KRTPTimestampToMS, true);
        m_pOveruseEstimator = new OveruseEstimator(options);
        m_pOveruseDetector = new OveruseDetector(options);
        mNow = 0;
    }
    
    OveruseDetectorTest::~OveruseDetectorTest()
    {
        if( m_pInterArrival ){
            delete m_pInterArrival;
            m_pInterArrival = nullptr;
        }
    
        if( m_pOveruseDetector ) {
            delete m_pOveruseDetector;
            m_pOveruseDetector = nullptr;
        }
    
        if( m_pOveruseEstimator ){
            delete m_pOveruseEstimator;
            m_pOveruseEstimator = nullptr;
        }
    }

    void OveruseDetectorTest::UpdateDetector(uint32_t rtp_timestamp, int64_t receive_timestamp, size_t packet_size)
    {
        uint32_t timestamp_delta;
        int64_t  arrive_time_delta;
        int      size_delta;
        
        if( m_pInterArrival->ComputeDeltas(rtp_timestamp, receive_timestamp, packet_size, &timestamp_delta, &arrive_time_delta, &size_delta)) {
            double timestamp_delta_ms = timestamp_delta / 90.0;
            m_pOveruseEstimator->Update(arrive_time_delta, timestamp_delta_ms, size_delta, m_pOveruseDetector->State());
            m_pOveruseDetector->Detect(m_pOveruseEstimator->offset(), timestamp_delta_ms, m_pOveruseEstimator->num_of_deltas(), receive_timestamp);
        }
    }
    
    void OveruseDetectorTest::GaussionRandom()
    {
        const static int MAX_BUCKET_SIZE = 100;
        int buckets[MAX_BUCKET_SIZE];
        
        memset(buckets, 0, sizeof(buckets));
        for( int i=0;i<10000;i++ ){
            int index = mRandom.Gaussian(49, 10);
            if( index >= 0 && index < MAX_BUCKET_SIZE ){
                buckets[index] ++;
            }
        }
        for( int i=0;i<MAX_BUCKET_SIZE;i++ ){
            printf("Bucket i:%d, %d\n", i, buckets[i]);
        }
    }
    
    void OveruseDetectorTest::SimpleNonOveruse30fps()
    {
        size_t packet_size = 1200;
        uint32_t  frame_duration_ms = 33;
        uint32_t  rtp_timestamp = 10*90;
        
        for( int i=0;i<1000;i++ ) {
            UpdateDetector(rtp_timestamp, mNow, packet_size);
            mNow += frame_duration_ms;
            rtp_timestamp += frame_duration_ms * 90;
            
            assert(kBwNormal == m_pOveruseDetector->State());
            //printf("%s\n", BandwdithState2String(m_pOveruseDetector->State()).c_str());
        }
    }
}
