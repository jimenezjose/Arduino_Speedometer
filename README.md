# Arduino_Speedometer
Inexpensive Arduino Speedometer add-on

Material Needed

Photoresister 
LED
White piece of paper

                 The light intensity of the black wheel has a standard 
                 deviation of 0.0. Although, I am calculating for the 
                 standard deviation of the wheels data, I noted that
                 it may not always be necessay. Hence for the symbolic
                 constant SIGNIFICANT_SCORE = 0. Of course if necessary 
                 under noisy conditions the SIGNIFICANT_SCORE value 
                 should be increased. 
                 Also, as the rpms increase the light intensity recieved 
                 from the photoresister decreases significantly hence if
                 the SIGNIFICANT_SCORE is increased it may cause revolutions
                 to not be counted.  
