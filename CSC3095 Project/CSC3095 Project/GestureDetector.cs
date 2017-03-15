using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Kinect;
using Microsoft.Kinect.VisualGestureBuilder;

namespace CSC3095_Project
{
    public class GestureDetector : IDisposable
    {
        //Variable accessing the VGB-built database where gestures are stored
        private readonly string gestureDatabase = @"W4ve.gbd";

        //Name of the waving gesture in the database
        private readonly string waveName = "W4ve";

        //Source of the gesture frames which will be tied to a tracked body's ID
        private VisualGestureBuilderFrameSource vgbFrameSource = null;

        //The gesture frame reader will handle all incoming gesture events from the sensor
        private VisualGestureBuilderFrameReader vbgFrameReader = null;

        public GestureDetector(KinectSensor kN, GestureResultView gRV)
        {

        }

        public void Dispose()
        {
            throw new NotImplementedException();
        }
    }
}
