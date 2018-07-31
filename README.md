# Arduino_Speedometer
Inexpensive Arduino Speedometer add-on

Materials Needed

Photoresister 
LED
White piece of paper

Idea:
    There is drastic change of light intensity from a material 
  that is black to a material that is white. To exploit such
  a discrete factor, a photoresistor is used as a light sensor 
  and an LED for noise control.

Implentation details:
    The light intensity of the black wheel has a standard 
  deviation of 0.0. Although, I am calculating for the 
  standard deviation of the wheels data, I noted that
  it may not always be necessary. Hence for the symbolic
  constant SIGNIFICANT_SCORE = 0. Of course if necessary 
  under noisy conditions the SIGNIFICANT_SCORE value 
  should be increased. 
    Also, to be noted, as the rpms increase the light intensity 
  received from the photoresistor decreases significantly. Hence
  with an incorrect revolution threshold (average + SIGNIFICANT_SCORE * stanDev), 
  it may be possible that the white piece of paper may not be noted. For more 
  insight look at the [images posted](../../Images).

[Images](../../Images):

  [Protype_Concept](../../Images/Protype_Concept):
    What do you mean by only a photoresistor, an LED, and a white strip of 
    of paper? 
  [Speedometer_data](../../Images/Speedometer_data):
    Real data from the a rotating wheel with a 0.25 SIGNIFICANT_SCORE.
    Every peak of light sensor data is the white strip of paper! 
  [Full_Throttle_Data](../../Images/Full_Throttle_Data):
    Real data from Arduino's Serial plotter with a SIGNIFICANT_SCORE = 0.
    This decision is evident in the data as, the peaks may have been missed
    if the revolution threshold was not equal to the mean.
  [Revolutions_Missed](../../Images/Revolutions_Missed):




             
