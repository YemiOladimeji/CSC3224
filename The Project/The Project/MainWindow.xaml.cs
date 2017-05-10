using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace The_Project
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        private string gesture;
        public event PropertyChangedEventHandler PropertyChanged;

        public MainWindow()
        {
            InitializeComponent();
            Gesture = string.Empty;
        }

        //Function to take the user to the next window and show content depending on the gesture they selected.
        private void Button_Click(object sender, RoutedEventArgs e)
        {

            if (exerciseListBox.SelectedIndex.Equals(0))
            {
                Gesture = "Karate Chop";
                var exercises = new Exercises(Gesture);
                exercises.Show();
                Close();

            } else if (exerciseListBox.SelectedIndex.Equals(1))
            {
                Gesture = "Arm Curl";
                var exercises = new Exercises(Gesture);
                exercises.Show();
                Close();

            } else if (exerciseListBox.SelectedIndex.Equals(2))
            {
                Gesture = "Push";
                var exercises = new Exercises(Gesture);
                exercises.Show();
                Close();

            } else if (exerciseListBox.SelectedIndex.Equals(3))
            {
                Gesture = "Wipe";
                var exercises = new Exercises(Gesture);
                exercises.Show();
                Close();

            } else if (exerciseListBox.SelectedIndex.Equals(4))
            {
                Gesture = "Wave";
                var exercises = new Exercises(Gesture);
                exercises.Show();
                Close();

            }
        }

        //When an option in the ListBox is selected, enable the continue button.
        private void Enable_Button(object sender, RoutedEventArgs e)
        {
            Select.IsEnabled = true;
        }

        //Property to get or set the current gesture the user has selected.
        public string Gesture
        {
            get
            {
                return gesture;
            }
            set
            {
                gesture = value ?? string.Empty;
                NotifyPropertyChanged();
                
            }
        }

        protected virtual void NotifyPropertyChanged([CallerMemberName] string propertyName = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

    }
}
