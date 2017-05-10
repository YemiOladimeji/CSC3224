using System;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows;
using System.Windows.Controls;

namespace The_Project
{
    /// <summary>
    /// Interaction logic for Exercises.xaml
    /// </summary>
    public partial class Exercises : Window, INotifyPropertyChanged
    {   
        private string difficultySetting = string.Empty;
        private string desc = string.Empty;

        //Zero-argument constructor
        public Exercises()
        {
            InitializeComponent();
            this.DataContext = this;
        }

        //Constructor with gesture choice as a parameter
        public Exercises(string gestureSelection)
        {
            InitializeComponent();
            if (gestureSelection == "Karate Chop")
            {
               vid.Source = new Uri(@"Videos/KarateChop.mp4", UriKind.Relative);
               dBox.Text = "Lift your arm up to your chest, take your forearm and bring it towards yourself. \nNow, stretch it out in a 'chopping' motion!That's the Karate Chop! Hi-yah!";
            }
            else if (gestureSelection == "Arm Curl")
            {
                vid.Source = new Uri(@"Videos/ArmCurl.mp4", UriKind.Relative);
                dBox.Text = "Curl your hand into a fist, take your forearm and pull it towards you! \nThen, stretch it out flat!That's the Arm Curl! Make those gains!";
            }
            else if (gestureSelection == "Push")
            {
                vid.Source = new Uri(@"Videos/Push.mp4", UriKind.Relative);
                dBox.Text = "Flatten your hand and lift it up to around chest height. \nNow, stretch your arm out until it's straight; as if your pushing something away from you! \nThat's the Push!";
            }
            else if (gestureSelection == "Wipe")
            {
                vid.Source = new Uri(@"Videos/Wipe.mp4", UriKind.Relative);
                dBox.Text = "Stretch your hand out flat and lift it up to around the height of your face. \nNow, move it around in a circular motion like you're wiping the windows! \nThat's the Wipe!";
            }
            else if (gestureSelection == "Wave")
            {
                vid.Source = new Uri(@"Videos/Wave.mp4", UriKind.Relative);
                dBox.Text = "Make your hand nice and flat and bring it up to the height of your face. \nNow, move it from left to right as if you're waving goodbye! That's the Wave!";
            }
            this.DataContext = this;
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void videoControl_Loaded(object sender, RoutedEventArgs e)
        {
            vid.Play();
        }

        //Loop the video playing
        private void videoControl_MediaEnded(object sender, RoutedEventArgs e)
        {
            vid.Position = TimeSpan.FromSeconds(0);
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Confirm.IsEnabled = true;
        }

        private void difficulty_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (difficultyListBox.SelectedIndex.Equals(0))
            {
                Difficulty = "Easy";
                difDesc.Text = "Easy: 5 repetitions! \nA good place to start!";
            }
            else if (difficultyListBox.SelectedIndex.Equals(1))
            {
                Difficulty = "Medium";
                difDesc.Text = "Medium: 10 repetitions! \nThings are starting to get harder!";

            }
            else if (difficultyListBox.SelectedIndex.Equals(2))
            {
                Difficulty = "Hard";
                difDesc.Text = "Hard: 20 repetitions! \nStarting to turn up the heat!";

            }
            else if (difficultyListBox.SelectedIndex.Equals(3))
            {
                Difficulty = "Extreme";
                difDesc.Text = "Extreme: 30 repetitions! \nNot for the faint of heart!";

            }
            else if (difficultyListBox.SelectedIndex.Equals(4))
            {
                Difficulty = "Extreme+";
                difDesc.Text = "Extreme+: 60 repetitions! \nYou should contact your OT or \nhave someone supervise \nyou before choosing this!";
            }
        }

        private void Confirm_Click(object sender, RoutedEventArgs e)
        {
            var game = new Game();
            game.Show();
            this.Close();
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            var home = new MainWindow();
            home.Show();
            this.Close();
        }

        //Property which gets and sets the current difficulty the user has selected.
        public string Difficulty
        {
            get
            {
                return difficultySetting;
            }
            private set
            {
                difficultySetting = value ?? string.Empty;
                NotifyPropertyChanged();
            }
        }

        //Property which gets and sets the description of the video.
        public string Description
        {
            get
            {
                return desc;
            }
            private set
            {
                desc = value ?? string.Empty;
                NotifyPropertyChanged();
            }
        }

        public MainWindow MainWindow { get; private set; }

        protected virtual void NotifyPropertyChanged([CallerMemberName] string propertyName = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
