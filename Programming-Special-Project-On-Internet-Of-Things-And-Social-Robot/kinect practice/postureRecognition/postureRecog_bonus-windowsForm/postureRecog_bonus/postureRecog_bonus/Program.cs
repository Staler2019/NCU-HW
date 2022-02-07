using System;
    using System.Collections.Generic;
    using System.Collections.ObjectModel;
    using System.ComponentModel;
    using System.Windows;
    using System.Windows.Controls;
    using Microsoft.Kinect;
    using Microsoft.Kinect.VisualGestureBuilder;

namespace postureRecog_bonus
{
    internal static class Program
    {
        static KinectSensor kinectSensor = null;
        static GestureResultView gestureResultView = null;
        static GestureDetector gestureDetector = null;
        static string statusText = null;


        // static KinectSensor kinectSensor = null;
        // static Body body = null;
        // static BodyFrameReader bodyFrameReader = null;
        // static string statusText = null;
        // // KinectBodyView kinectBodyView = null;
        // static GestureDetector gestureDetector = null;
        // Body[] bodies = null;
        // List<GestureDetector> gestureDetectorList = null;

        [STAThread]
        static void Main()
        {
            InitKinectSensor();
            // system build
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());

            // my code
            kinectController = new KinectController();
        }

        static void InitKinectSensor(){
            this.kinectSensor = KinectSensor.GetDefault();
            this.kinectSensor.IsAvailableChanged += this.Sensor_IsAvailableChanged;
            this.kinectSensor.Open();
            this.statusText = this.kinectSensor.IsAvailable ? Properties.Resources.RunningStatusText 
                                                            : Properties.Resources.NoSensorStatusText;
            this.gestureResultView = new GestureResultView(0, false, false, 0.0f);
            this.gestureDetector = new GestureDetector(this.kinectSensor, result);
        }

        public event PropertyChangedEventHandler PropertyChanged;

        public string StatusText
        {
            get
            {
                return this.statusText;
            }

            set
            {
                if (this.statusText != value)
                {
                    this.statusText = value;

                    // notify any bound elements that the text has changed
                    if (this.PropertyChanged != null)
                    {
                        this.PropertyChanged(this, new PropertyChangedEventArgs("StatusText"));
                    }
                }
            }
        }
        static void CloseKinectSensor(){
            if (this.gestureDetector != null){
            this.gestureDector.Dispose();}
            if (this.kinectSensor != null)
            {
                this.kinectSensor.IsAvailableChanged -= this.Sensor_IsAvailableChanged;
                this.kinectSensor.Close();
                this.kinectSensor = null;
            }
        }

        static void Sensor_IsAvailableChanged(object sender, IsAvailableChangedEventArgs e)
        {
            // on failure, set the status text
            this.StatusText = this.kinectSensor.IsAvailable ? Properties.Resources.RunningStatusText
                                                            : Properties.Resources.SensorNotAvailableStatusText;
        }
    }

}
