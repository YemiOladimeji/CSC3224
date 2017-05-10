using System;
using System.Collections.Generic;
using Microsoft.Kinect;
using Microsoft.Kinect.VisualGestureBuilder;

namespace The_Project
{
    public class GestureDetector : IDisposable
    {
        //Variable accessing the VGB-built database where gestures are stored.
        private readonly string gestureDatabase = @"Database\ReUP.gbd";

        //Names of the gestures in the database.
        private readonly string aclName = "ArmCurl_Left";
        private readonly string kclName = "KarateChop_Left";
        private readonly string plName = "Push_Left";
        private readonly string walName = "Wave_Left";
        private readonly string wilName = "Wipe_Left";

        private readonly string acrName = "ArmCurl_Right";
        private readonly string kcrName = "KarateChop_Right";
        private readonly string prName = "Push_Right";
        private readonly string warName = "Wave_Right";
        private readonly string wirName = "Wipe_Right";

        //Source of the gesture frames which will be tied to a tracked body's ID.
        private VisualGestureBuilderFrameSource vgbFrameSource = null;

        //The gesture frame reader will handle all incoming gesture events from the sensor.
        private VisualGestureBuilderFrameReader vgbFrameReader = null;

        //Access properties for classes which have data which needs to be displayed in the UI.
        public GestureResultView GestureResultView { get; private set; }
        public Game Game { get; private set; }
        public MainWindow MainWindow { get; private set; }
        public Exercises Exercises { get; private set; }

        //Constructor to initialise a new instance of the GestureDetector class.
        public GestureDetector(KinectSensor kN, GestureResultView gRV)
        {
            if (kN == null)
            {
                throw new ArgumentNullException("kN");
            }
            if (gRV == null)
            {
                throw new ArgumentNullException("gRV");
            }

            this.GestureResultView = gRV;
            
            //Create the VisualGesturebuilder source. The ID of the body to track will be set when a valid body frame arrives from the sensor.
            this.vgbFrameSource = new VisualGestureBuilderFrameSource(kN, 0);
            this.vgbFrameSource.TrackingIdLost += this.Source_TrackingIdLost;

            //Open the reader for the VGB frames.
            this.vgbFrameReader = this.vgbFrameSource.OpenReader();
            if (this.vgbFrameReader != null)
            {
                this.vgbFrameReader.IsPaused = true;
                this.vgbFrameReader.FrameArrived += this.Reader_GestureFrameArrived;
            }

            //Load all of the available gestures into the database.
            using (VisualGestureBuilderDatabase dB = new VisualGestureBuilderDatabase(this.gestureDatabase))
            {
                this.vgbFrameSource.AddGestures(dB.AvailableGestures);
            }
        }

        //Function to handle the gesture detection results arriving from the sensor.
        private void Reader_GestureFrameArrived(object sender, VisualGestureBuilderFrameArrivedEventArgs e)
        {
            VisualGestureBuilderFrameReference frameReference = e.FrameReference;
            using (VisualGestureBuilderFrame frame = frameReference.AcquireFrame())
            {
                if (frame != null)
                {
                    //Get the gesture results from the last frame.
                    IReadOnlyDictionary<Gesture, DiscreteGestureResult> discreteResults = frame.DiscreteGestureResults;

                    if (discreteResults != null)
                    {
                        foreach (Gesture gesture in this.vgbFrameSource.Gestures)
                        {
                            if (gesture.GestureType == GestureType.Discrete)
                            {
                                DiscreteGestureResult result = null;
                                discreteResults.TryGetValue(gesture, out result);

                                if (result != null && result.Confidence > 0.8) //Limit the amount of results which are reported back, by setting a minimum confidence level.
                                {
                                    if (result.Detected == true && result.Confidence > 0.8)
                                    {
                                        this.GestureResultView.GestureCount++; //Update the successful number of gestures performed.
                                    }
                                    this.GestureResultView.UpdateGestureResult(true, result.Detected, result.Confidence); //Report back the updated gesture result.                       
                                }
                            }
                        }
                    }
                }
            }
        }

        //Property which gets or sets the tracking ID associated with the current detector.
        public ulong TrackingId
        {
            get
            {
                return this.vgbFrameSource.TrackingId;
            }

            set
            {
                if (this.vgbFrameSource.TrackingId != value)
                {
                    this.vgbFrameSource.TrackingId = value;
                }
            }
        }

        //Property which sets or gets a value indicating whether the detector is paused or not.
        public bool IsPaused
        {
            get
            {
                return this.vgbFrameReader.IsPaused;
            }

            set
            {
                if (this.vgbFrameReader.IsPaused != value)
                {
                    this.vgbFrameReader.IsPaused = value;
                }
            }
        }

        //Function which disposes of all unmanaged resources for this class.
        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }

        //Function which disposes of all the VisualGestureBuilderFrameReader and VisualGestureBuilderFrameSource objects.
        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                if (this.vgbFrameReader != null)
                {
                    this.vgbFrameReader.FrameArrived -= this.Reader_GestureFrameArrived;
                    this.vgbFrameReader.Dispose();
                    this.vgbFrameReader = null;
                }

                if (this.vgbFrameSource != null)
                {
                    this.vgbFrameSource.TrackingIdLost -= this.Source_TrackingIdLost;
                    this.vgbFrameSource.Dispose();
                    this.vgbFrameSource = null;
                }
            }
        }

        //Function which handles the TrackingIdLost event for the VisualGestureBuilderSource object.
        private void Source_TrackingIdLost(object sender, TrackingIdLostEventArgs e)
        {
            this.GestureResultView.UpdateGestureResult(false, false, 0.0f);
        }

    }
}