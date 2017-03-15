using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSC3095_Project
{
    public class GestureResultView : INotifyPropertyChanged
    {
        //Change to be true, if the user is detected performing a waving gesture
        private bool waving = false;

        //Change to be true, if the discrete gesture being peformed matches one in the database and is being detected
        private bool detected = false;

        //Current confidence value reported by the gesture, can be used to verify the validity of certain gestures
        private float confidence = 0.0f;

        public event PropertyChangedEventHandler PropertyChanged;

        public GestureResultView(bool waving, bool detect, float con)
        {
            this.waving = waving;
            this.Detected = detect;
            this.Confidence = con;
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

        public bool Waving
        {
            get
            {
                return this.waving;
            }

            private set
            {
                if (this.waving != value)
                {
                    this.waving = value;
                    this.NotifyPropertyChanged();
                }
            }
        }


        public void UpdateGestureResult(bool wave, bool isGestureDetected, float dCon)
        {
            this.Confidence = 0.0f;

            this.Detected = isGestureDetected;

            if (this.Detected)
            {
                this.Waving = true;
                this.Confidence = dCon;
            } else
            {
                this.Detected = false;
                isGestureDetected = false;
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
