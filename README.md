# Arduino_Speedometer
Inexpensive Arduino Speedometer add-on

### Materials Needed
    Photoresister 
    
    LED
    
    White piece of paper

### Idea:
    There is drastic change of light intensity from a material
    that is black to a material that is white. To exploit such
    a discrete factor, a photoresistor is used as a light sensor 
    and an LED for noise control.

### Implentation details:
      The light intensity of the black wheel has a standard 
    deviation of 0.0. Although, I am calculating for the 
    standard deviation of the wheels data, I noted that
    it may not always be necessary. Hence for the symbolic
    constant SIGNIFICANT_SCORE = 0 in the code. Of course if necessary, 
    under noisy conditions the SIGNIFICANT_SCORE value 
    should be increased. 
      Also, to be noted, as the rpms increase the light intensity 
    received from the photoresistor decreases significantly. Hence
    with an incorrect revolution threshold (average + SIGNIFICANT_SCORE * stanDev), 
    it may be possible that the white piece of paper may not be noted. For more 
    insight look at the images posted.

### [Images](https://github.com/jimenezjose/Arduino_Speedometer/tree/master/Images):

####  [Protype_Concept](https://github.com/jimenezjose/Arduino_Speedometer/blob/master/Images/Prototype_Concept.jpg):
    What do you mean by only a photoresistor, an LED, and a white strip of 
    of paper? 
####  [Speedometer_data](https://github.com/jimenezjose/Arduino_Speedometer/blob/master/Images/Speedometer_data.png):
    Real data from the a rotating wheel with a 0.25 SIGNIFICANT_SCORE.
    Every peak of light sensor data is the white strip of paper! 
####  [Full_Throttle_Data](https://github.com/jimenezjose/Arduino_Speedometer/blob/master/Images/Full_Throttle_Data.png):
    Real data from Arduino's Serial plotter with a SIGNIFICANT_SCORE = 0.
    This decision is evident in the data as, the peaks may have been missed
    if the revolution threshold was not equal to the mean.
####  [Revolutions_Missed](https://github.com/jimenezjose/Arduino_Speedometer/blob/master/Images/Revolutions_Missed.png):
    Real data from the rotating wheel showing how a wrong revolution 
    threshold (SIGNIFICANT_SCORE deviations from the mean) may result in 
    missing a ratation. The circled sections from the image demonstrate how
    a peak did not surpass the green line (revolution threshold).



             
