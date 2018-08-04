# Arduino_Speedometer
Inexpensive Arduino Speedometer 

### Materials Needed
    Photoresistor 
    
    LED
    
    White strip of paper

### Idea:
      There is drastic change of light intensity from a material that is black to a material that is white. 
    To exploit such a discrete factor, a photoresistor is used as a light sensor and an LED for noise 
    control.

### Implementation details:
      The light intensity of the black wheel has a standard  deviation 1.0. Meaning when the photoresistor
    is under one contant light intensity, its sensor value deviates randomly between two adjacent integers.
    Although, I calculate for the standard deviation of the wheels data, I noted that it may not always be  
    necessary. Hence for the symbolic constant SIGNIFICANT_SCORE = 0 in the code. Of course if necessary,  
    under noisy conditions the SIGNIFICANT_SCORE value should be increased. The SIGNIFICANT_SCORE is what I
    call the revolution threshold, in the images posted, it is labeled as the number of standard deviations
    from the mean.
      Also, to be noted, as the rpms increase the light intensity received from the photoresistor decreases 
    significantly. Hence with an incorrect revolution threshold (average + SIGNIFICANT_SCORE * stanDev), 
    it may be possible that the white piece of paper may not be noted. For more insight look at 
    image "Revolutions_Missed".

### [Images](https://github.com/jimenezjose/Arduino_Speedometer/tree/master/Images):

####  [Protype_Concept](https://github.com/jimenezjose/Arduino_Speedometer/blob/master/Images/Prototype_Concept.jpg):
    What do you mean by only a photoresistor, an LED, and a white strip of of paper? 
![alt text]( https://github.com/jimenezjose/Arduino_Speedometer/blob/master/Images/Prototype_Concept.jpg "Prototype")

####  [Speedometer_data](https://github.com/jimenezjose/Arduino_Speedometer/blob/master/Images/Speedometer_data.png):
    Real data from the a rotating wheel with a 0.25 SIGNIFICANT_SCORE (revolution threshold - stanDev from the mean). 
    Every peak of light sensor data is the white strip of paper! 
![alt text]( https://github.com/jimenezjose/Arduino_Speedometer/blob/master/Images/Speedometer_data.png "Speedometer data")
    
####  [Full_Throttle_Data](https://github.com/jimenezjose/Arduino_Speedometer/blob/master/Images/Full_Throttle_Data.png):
    Real data from Arduino's Serial plotter with a SIGNIFICANT_SCORE = 0. This decision is evident in the
    data as, the peaks may have been missed if the revolution threshold was not equal to the mean.
![alt text]( https://github.com/jimenezjose/Arduino_Speedometer/blob/master/Images/Full_Throttle_Data.png "Full Throttle data")
  
####  [Revolutions_Missed](https://github.com/jimenezjose/Arduino_Speedometer/blob/master/Images/Revolutions_Missed.png):
    Real data from the rotating wheel showing how a wrong revolution threshold 
    (SIGNIFICANT_SCORE deviations from the mean) may result in missing a rotation. The circled sections
    from the image demonstrate how a peak did not surpass the green line (revolution threshold) and hence 
    missing a wheel rotation.
![alt text]( https://github.com/jimenezjose/Arduino_Speedometer/blob/master/Images/Revolutions_Missed.png "Revolutions Missed")

#### [UPDATE]: [Noise_Control](https://github.com/jimenezjose/Arduino_Speedometer/blob/master/Images/Noise_Control.png):
    As mentioned in the Readme section "implementation detail", when the photoresistor is under a constant
    light intensity, the light sensor values deviate with a standard deviation of 1.0. Meaning the light
    sensor value randomly deviate between two adjacent integers under no light differential. Therefore,
    as a solution: once the current light value has a differential greater than 1.0 then the current
    sensor reading is validated, otherwise the current light value is considered noise and thus disregarded.
    Resulting to beautiful discrete light values.
__Before:__
![alt text]( https://github.com/jimenezjose/Arduino_Speedometer/blob/master/Images/No_Noise_Control.png "No Noise Control")
__After:__
![alt text]( https://github.com/jimenezjose/Arduino_Speedometer/blob/master/Images/Noise_Control.png "Noise Control")

#### [New_Speedometer_Data](https://github.com/jimenezjose/Arduino_Speedometer/blob/master/Images/Noise_Control2.png):
![alt text]( https://github.com/jimenezjose/Arduino_Speedometer/blob/master/Images/Noise_Control2.png "Noise Control2")
