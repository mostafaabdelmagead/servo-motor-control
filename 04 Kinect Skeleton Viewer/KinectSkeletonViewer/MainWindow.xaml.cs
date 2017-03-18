using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Net.Sockets;


using Microsoft.Kinect;
using System.IO;

namespace KinectSkeletonViewer
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        KinectSensor myKinect;
        System.Net.Sockets.TcpClient clientSocket = new System.Net.Sockets.TcpClient();

        public MainWindow()
        {
            InitializeComponent();
            clientSocket.Connect("10.0.0.216", 5005);
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {

            // Check to see if a Kinect is available
            if (  KinectSensor.KinectSensors.Count == 0)
            {
                MessageBox.Show("No Kinects detected", "Camera Viewer");
                Application.Current.Shutdown();
            }

            // Get the first Kinect on the computer
            myKinect = KinectSensor.KinectSensors[0];

            // Start the Kinect running and select the depth camera
            try
            {
                myKinect.SkeletonStream.Enable();
                myKinect.Start();
            }
            catch
            {
                MessageBox.Show("Kinect initialise failed", "Camera Viewer");
                Application.Current.Shutdown();
            }

            // connect a handler to the event that fires when new frames are available

            myKinect.SkeletonFrameReady += new EventHandler<SkeletonFrameReadyEventArgs>(myKinect_SkeletonFrameReady);

        }

        Brush skeletonBrush = new SolidColorBrush(Colors.Blue);

        void addLine(Joint j1, Joint j2)
        {
            Line boneLine = new Line();
            boneLine.Stroke = skeletonBrush;
            boneLine.StrokeThickness = 5;
            float j1X, j1Y;

            DepthImagePoint j1P = myKinect.MapSkeletonPointToDepth(j1.Position, DepthImageFormat.Resolution640x480Fps30);
            boneLine.X1 = j1P.X;
            boneLine.Y1 = j1P.Y;

            DepthImagePoint j2P = myKinect.MapSkeletonPointToDepth(j2.Position, DepthImageFormat.Resolution640x480Fps30);
            boneLine.X2 = j2P.X;
            boneLine.Y2 = j2P.Y;

            skeletonCanvas.Children.Add(boneLine);
        }

        void myKinect_SkeletonFrameReady(object sender, SkeletonFrameReadyEventArgs e)
        {
            string leftArmMessage = "No Skeleton Data";
            string rightArmMessage = "No Skeleton Data";
            string spineMessage = "No Skeleton Data";
            string qualityMessage = "";

            // Remove the old skeleton
            skeletonCanvas.Children.Clear();
            Brush brush = new SolidColorBrush(Colors.Blue);

            SkeletonFrame frame = e.OpenSkeletonFrame();

            if (frame == null) return;

            Skeleton[] skeletons = new Skeleton[frame.SkeletonArrayLength];
            frame.CopySkeletonDataTo(skeletons);

            foreach (Skeleton skeleton in skeletons)
            {
                if (skeleton.TrackingState == SkeletonTrackingState.Tracked)
                {
                    Joint headJoint = skeleton.Joints[JointType.Head];
                    Joint hipCenter = skeleton.Joints[JointType.HipCenter];


                    if (headJoint.TrackingState != JointTrackingState.NotTracked)
                    {
                        SkeletonPoint headPosition = headJoint.Position;

                      //  message = string.Format("Head: X:{0:0.0} Y:{1:0.0} Z:{2:0.0}",
                       //     headPosition.X,
                         //   headPosition.Y,
                          //  headPosition.Z);

                        if (headJoint.TrackingState == JointTrackingState.Inferred)
                        {
                           // message = message + " I";
                        }

                        // Spine
                        addLine(skeleton.Joints[JointType.Head], skeleton.Joints[JointType.ShoulderCenter]);
                        addLine(skeleton.Joints[JointType.ShoulderCenter], skeleton.Joints[JointType.Spine]);

                        //DepthImagePoint head = myKinect.MapSkeletonPointToDepth(skeleton.Joints[JointType.Head].Position
                         //                                                            , DepthImageFormat.Resolution640x480Fps30);
                        //DepthImagePoint shldrCenter = myKinect.MapSkeletonPointToDepth(skeleton.Joints[JointType.ShoulderCenter].Position
                          //                                                           , DepthImageFormat.Resolution640x480Fps30);
                       // DepthImagePoint spine = myKinect.MapSkeletonPointToDepth(skeleton.Joints[JointType.Spine].Position
                       //                                                           , DepthImageFormat.Resolution640x480Fps30);
                       SkeletonPoint head = skeleton.Joints[JointType.Head].Position;
                       SkeletonPoint shldrCenter = skeleton.Joints[JointType.ShoulderCenter].Position;
                       SkeletonPoint spine = skeleton.Joints[JointType.Spine].Position;



                       spineMessage = string.Format("head.x:{0:0.0}  head.y:{1:0.0}  head.z:{2:0.0} , shldrCenter.x:{3:0.0} shldrCenter.y:{4:0.0}  shldrCenter.y:{5:0.0} , spine.x:{6:0.0} spine.y:{7:0.0} spine.z:{8:0.0}"
                                                    , head.X , head.Y , head.Z,  shldrCenter.X, shldrCenter.Y , shldrCenter.Z, spine.X , spine.Y, spine.Z);

                        // Left leg
                        //addLine(skeleton.Joints[JointType.Spine], skeleton.Joints[JointType.HipCenter]);
                        //addLine(skeleton.Joints[JointType.HipCenter], skeleton.Joints[JointType.HipLeft]);
                        //addLine(skeleton.Joints[JointType.HipLeft], skeleton.Joints[JointType.KneeLeft]);
                        //addLine(skeleton.Joints[JointType.KneeLeft], skeleton.Joints[JointType.AnkleLeft]);
                        //addLine(skeleton.Joints[JointType.AnkleLeft], skeleton.Joints[JointType.FootLeft]);

                        // Right leg
                        //addLine(skeleton.Joints[JointType.HipCenter], skeleton.Joints[JointType.HipRight]);
                        //addLine(skeleton.Joints[JointType.HipRight], skeleton.Joints[JointType.KneeRight]);
                        //addLine(skeleton.Joints[JointType.KneeRight], skeleton.Joints[JointType.AnkleRight]);
                        //addLine(skeleton.Joints[JointType.AnkleRight], skeleton.Joints[JointType.FootRight]);

                        // Left arm
                        addLine(skeleton.Joints[JointType.ShoulderCenter], skeleton.Joints[JointType.ShoulderLeft]);
                        addLine(skeleton.Joints[JointType.ShoulderLeft], skeleton.Joints[JointType.ElbowLeft]);
                        addLine(skeleton.Joints[JointType.ElbowLeft], skeleton.Joints[JointType.WristLeft]);
                        addLine(skeleton.Joints[JointType.WristLeft], skeleton.Joints[JointType.HandLeft]);
                        /*
                        DepthImagePoint shldrlft = myKinect.MapSkeletonPointToDepth(skeleton.Joints[JointType.ShoulderLeft].Position
                                                                                     ,DepthImageFormat.Resolution640x480Fps30);
                        DepthImagePoint elblft = myKinect.MapSkeletonPointToDepth(skeleton.Joints[JointType.ElbowLeft].Position
                                                                                     ,DepthImageFormat.Resolution640x480Fps30);                        
                        DepthImagePoint wrstlft = myKinect.MapSkeletonPointToDepth(skeleton.Joints[JointType.WristLeft].Position
                                                                                     ,DepthImageFormat.Resolution640x480Fps30);
                        DepthImagePoint hndlft = myKinect.MapSkeletonPointToDepth(skeleton.Joints[JointType.HandLeft].Position
                                                                                     , DepthImageFormat.Resolution640x480Fps30);
                         * */
                        SkeletonPoint shldrlft = skeleton.Joints[JointType.ShoulderLeft].Position;
                        SkeletonPoint elblft = skeleton.Joints[JointType.ElbowLeft].Position;
                        SkeletonPoint wrstlft = skeleton.Joints[JointType.WristLeft].Position;
                        SkeletonPoint hndlft = skeleton.Joints[JointType.HandLeft].Position;

                        leftArmMessage = string.Format("shldrlft.x:{0:0.0} shldrlft.Y:{1:0.0} shldrlft.z:{2:0.0} , elblft.x:{3:0.0} elblft.Y:{4:0.0} elblft.z:{5:0.0} , wrstlft.x:{6:0.0} wrstlft.y:{7:0.0} wrstlft.z:{8:0.0} \n, hndtlft.x:{9:0.0} hndlft.y:{10:0.0} hndlft.z:{11:0.0} "
                                                        , shldrlft.X, shldrlft.Y, shldrlft.Z, elblft.X, elblft.Y, elblft.Z, wrstlft.X, wrstlft.Y, wrstlft.Z, hndlft.X, hndlft.Y, hndlft.Z);

                        // Right arm
                        addLine(skeleton.Joints[JointType.ShoulderCenter], skeleton.Joints[JointType.ShoulderRight]);
                        addLine(skeleton.Joints[JointType.ShoulderRight], skeleton.Joints[JointType.ElbowRight]);
                        addLine(skeleton.Joints[JointType.ElbowRight], skeleton.Joints[JointType.WristRight]);
                        addLine(skeleton.Joints[JointType.WristRight], skeleton.Joints[JointType.HandRight]);
                        /*
                        DepthImagePoint shldrRight = myKinect.MapSkeletonPointToDepth(skeleton.Joints[JointType.ShoulderRight].Position
                                                                                    , DepthImageFormat.Resolution640x480Fps30);
                        DepthImagePoint elbRight = myKinect.MapSkeletonPointToDepth(skeleton.Joints[JointType.ElbowRight].Position
                                                                                  , DepthImageFormat.Resolution640x480Fps30);
                        DepthImagePoint wrstRight = myKinect.MapSkeletonPointToDepth(skeleton.Joints[JointType.WristRight].Position
                                                                                     , DepthImageFormat.Resolution640x480Fps30);
                        DepthImagePoint hndRight = myKinect.MapSkeletonPointToDepth(skeleton.Joints[JointType.HandRight].Position
                                                                                     , DepthImageFormat.Resolution640x480Fps30);
                         * */
                        SkeletonPoint shldrRight = skeleton.Joints[JointType.ShoulderRight].Position;
                        SkeletonPoint elbRight = skeleton.Joints[JointType.ElbowRight].Position;
                        SkeletonPoint wrstRight = skeleton.Joints[JointType.WristLeft].Position;
                        SkeletonPoint hndRight = skeleton.Joints[JointType.HandLeft].Position;

                        rightArmMessage = string.Format("shldrRight.x:{0:0.0} shldrRight.Y:{1:0.0} shldrRight.z:{2:0.0} , elbRight.x:{3:0.0} elbRight.Y:{4:0.0} elbRight.z:{5:0.0} , wrstlft.x:{6:0.0} wrstlft.y:{7:0.0} wrstlft.z:{8:0.0} \n, hndtlft.x:{9:0.0} hndlft.y:{10:0.0} hndlft.z:{11:0.0} "
                                                         , shldrRight.X, shldrRight.Y, shldrRight.Z, elbRight.X, elbRight.Y, elbRight.Z, wrstRight.X, wrstRight.Y, wrstRight.Z, hndRight.X, hndRight.Y, hndRight.Z);



                    }
                }
            }

            StatusTextBlock.Text = leftArmMessage;
            RightArmTextBlock.Text = rightArmMessage;
            SpineTextBlock.Text = spineMessage;
            NetworkStream serverStream = clientSocket.GetStream();
            byte[] outStream = System.Text.Encoding.ASCII.GetBytes(StatusTextBlock.Text + "$");
            serverStream.Write(outStream, 0, outStream.Length);
            serverStream.Flush();

            QualityTextBlock.Text = qualityMessage;
        }
    }
}
