using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace CSC3095_Project
{
    public class GestureResultView : INotifyPropertyChanged
    {
        private int bodyID = 0;

        //Change to be true, if the discrete gesture being peformed matches one in the database and is being detected
        private bool detected = false;

        //Current confidence value reported by the gesture, can be used to verify the validity of certain gestures
        private float confidence = 0.0f;

        //True, if the current body is being tracked successfully
        private bool isTracked = false;

        //Integer to track the amount of times a gesture has been performed
        private int gestureCount = 0;

        public event PropertyChangedEventHandler PropertyChanged;

        public GestureResultView(int bID, bool detect, bool track, float con, int gCount)
        {       
            this.BodyID = bID;
            this.Detected = detect;
            this.IsTracked = track;
            this.Confidence = con;
            this.GestureCount = gCount;
        }

        public int BodyID
        {
            get
            {
                return this.bodyID;
            }

            private set
            {
                if (this.bodyID != value)
                {
                    this.bodyID = value;
                    this.NotifyPropertyChanged();
                }
            }
        }

        public int GestureCount
        {
            get
            {
                return this.gestureCount;
            }

            set
            {
                if (this.gestureCount != value)
                {
                    this.gestureCount = value;
                    this.NotifyPropertyChanged();
                }
            }
        }

        public bool Detected
        {
            get
            {
                return this.detected;
            }

            private set
            {
                if (this.detected != value)
                {
                    this.detected = value;
                    this.NotifyPropertyChanged();
                }
            }
        }

        public float Confidence
        {
            get
            {
                return this.confidence;
            }

            private set
            {
                if (this.confidence != value)
                {
                    this.confidence = value;
                    this.NotifyPropertyChanged();
                }
            }
        }

        public bool IsTracked
        {
            get
            {
                return this.isTracked;
            }

            private set
            {
                if (this.isTracked != value)
                {
                    this.isTracked = value;
                    this.NotifyPropertyChanged();
                }
            }
        }


        //Updates the values associated with the discrete gesture detection result
        public void UpdateGestureResult(bool isBodyTrackingIDValid, bool isGestureDetected, float detectionConfidence)
        {
            this.IsTracked = isBodyTrackingIDValid;
            this.Confidence = 0.0f;

            if (!this.IsTracked)
            {
                this.Detected = false;
            }
            else
            {
                this.Detected = isGestureDetected;

                if (this.Detected)
                {
                    this.Confidence = detectionConfidence;
                }
            }
        }

        private void NotifyPropertyChanged([CallerMemberName] string propertyName = "")
        {
            if (this.PropertyChanged != null)
            {
                this.PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }
    }
}
