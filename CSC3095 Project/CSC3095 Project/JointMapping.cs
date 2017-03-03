using Microsoft.Kinect;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;


namespace CSC3095_Project
{
    public static class JointMapping
    {
        public static Joint ScaleTo(this Joint joint, double width, double height, float bodyMaxX, float bodyMaxY)
        {
            joint.Position = new CameraSpacePoint
            {
                X = Scale(width, bodyMaxX, joint.Position.X),
                Y = Scale(height, bodyMaxY, -joint.Position.Y),
                Z = joint.Position.Z
            };

            return joint;
        }

        public static Joint ScaleTo(this Joint joint, double width, double height)
        {
            return ScaleTo(joint, width, height, 1.0f, 1.0f);
        }

        private static float Scale(double maxPixel, double maxBody, float position)
        {
            float value = (float)((((maxPixel / maxBody) / 2) * position) + (maxPixel / 2));

            if (value > maxPixel)
            {
                return (float)maxPixel;
            }

            if (value < 0)
            {
                return 0;
            }

            return value;
        }


        /*public static void DrawPoint(this Canvas canvas, Joint joint)
        {
            if (joint.TrackingState == TrackingState.NotTracked) { }
            return;

            joint = joint.ScaleTo(canvas.ActualWidth, canvas.ActualHeight);

            Ellipse e = new Ellipse
            {
                Width = 20,
                Height = 20,
                Fill = new SolidColorBrush(Colors.DarkGoldenrod)
            };

            Canvas.SetLeft(e, joint.Position.X - e.Width / 2);
            Canvas.SetRight(e, joint.Position.Y - e.Height / 2);

            canvas.Children.Add(e);
        }*/
    }
}
