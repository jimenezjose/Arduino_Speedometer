# Arduino_Speedometer
Inexpensive Arduino Speedometer add-on

Material Needed

Photoresister 
LED
White piece of paper

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

Images:






             
