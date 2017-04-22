using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSC3095___Project
{
    class GestureResultView : INotifyPropertyChanged
    {
        //The body index associated with the current gesture detector
        private int bodyIndex = 0;

        //Confidence value reported by the discrete gesture
        private float confidence = 0.0f;

        //Boolean which reports whether the gesture is being detected or not
        private bool detected = false;

        //Boolean which reports whether the body is being tracked or not
        private bool isTracked = false;

        public event PropertyChangedEventHandler PropertyChanged;

        public GestureResultView(int bodyIndex, bool isTracked, bool detected, float confidence)
        {

        }

        //Gets the body index associated with the current gesture detector result
        public int BodyIndex
        {
            get
            {
                return this.bodyIndex;
            }

            private set
            {
                if (this.bodyIndex != value)
                {
                    this.bodyIndex = value;
                    this.NotifyPropertyChanged();
                }
            }
        }

        //Gets a value indicating or not the body associated with the gesture detector is tracked
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

        //Gets a value indicating whether or not the discrete gesture has been detected
        public bool Detected
        {
            get
            {
                return this.detected;
            }

            private set
            {
                if (this.detected != value){
                    this.detected = value;
                    this.NotifyPropertyChanged();
                }
            }
        }

        //Gets a value which indicated the detector's confdence that the gesture is occurring
        public float Confidence
        {
            get
            {
                return this.confidence;
            }

            private set
            {
                if (this.confidence !=  value)
                {
                    this.confidence = value;
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
            } else
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
