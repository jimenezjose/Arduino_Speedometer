/****************************************************************************

                                                Jose Jorge Jimenez-Olivas
                                                August 1, 2018

                            Speedometer

File Name:       Speedometer.ino
Description:     With a white strip of paper, a photoresister, and an
                 LED, a speedometer can be easily implemented using 
                 statistical testing. the first seconds of the program 
                 will be used to collect data and calculate the standard
                 deviation and the mean. Ensure that the respective wheel 
                 is rotating for a positively skewed mean 
                 (skewed mean compaered to a mean from a non-rotating wheel)
****************************************************************************/
#define SAMPLE_SIZE 100
#define SIGNIFICANT_SCORE 0.01  /* Number of Standard Deviations from the Mean */

void populateData( int *, int, const int );
double getAverage( int *, int );
double getStanDev( int *, int, double );

const int sensorPin = A0;        /* photoresister pin */
const int ledPin = 12;           /* led to help cut noise from data */

int data[ SAMPLE_SIZE ] = { 0 }; /* sample of data from wheel turning */
double average = 0;              /* average value from data */
double stanDev = 0;              /* standard deviation from data */        
boolean reading = true;          /* ready for white line to pass */
unsigned long previousMillis = 0;/* used for calculating time without delays */
long revolutions = 0;            /* revoultions of wheel */
long maxRPM = 0;                 /* max rpm in duration of program */

long temp = 0; //TODO
int prevLight = 0;

void setup() {
  Serial.begin( 9600 );
  pinMode( sensorPin, INPUT );
  pinMode( ledPin, OUTPUT );

  delay( 100 );
  digitalWrite( ledPin, HIGH );

  populateData( data, SAMPLE_SIZE, sensorPin );
  average = getAverage( data, SAMPLE_SIZE );
  stanDev = getStanDev( data, SAMPLE_SIZE, average );
 
  Serial.print( "Average: " );
  Serial.println( average );
  Serial.print( "Standard Deviation: " );
  Serial.println( stanDev );
   
}

void loop() {

  int currLight = analogRead( sensorPin );

  /* Noise Control -- avoid currLight to bounce between two adjacent values */
  ( abs(currLight - prevLight) > 1 ) ? prevLight = currLight : currLight = prevLight;
  
  double Z_Score = (currLight - average) / stanDev;
  long rpm;
      
  if( reading && Z_Score > SIGNIFICANT_SCORE ) {
    /* 1 revolution noted, beginning of peak */
    revolutions++;
    temp++;
    reading = false;
  }
  else if( !reading && Z_Score <= SIGNIFICANT_SCORE) {
    /* peak fell below Z_Score threshold */
    reading = true;
  }

  unsigned long currentMillis = millis();
  if( revolutions ) {
    /* revolutions per minute */
    double dt = currentMillis - previousMillis;
    dt = dt * (1.0 / 1000);// * ( 1.0 / 60);
    //Serial.print( "delta time: " );
    //Serial.println( dt );
    rpm = revolutions / dt;
    //Serial.print( "rpm: " );
    //Serial.println( rpm );
    previousMillis = currentMillis;
    revolutions = 0;
    
    if( rpm > maxRPM ) {
      /* new max */
      maxRPM = rpm;
    }
  }
 
    Serial.print( /*revolutions*/ temp );
    Serial.print( "\t" );
    //Serial.print( "Y: " );
    Serial.print( currLight );
    Serial.print( "\t" );
    Serial.print( average + SIGNIFICANT_SCORE * stanDev );
    Serial.print( "\t" );
    Serial.println( rpm );
    

}

/***************************************************************************
% Routine Name : populateData
% File :         Speedometer.ino
% Parameters:    data      -- array of to be filled with sensorPin readings
%                dataSize  -- size of array data 
%                sensorPin -- sensor to be retrieving data from
% Description :  read data from sensorPin and fill array "data" with 
%                raw readings
% Return:        Nothing
***************************************************************************/
void populateData( int * data, int dataSize, const int sensorPin ) {
  long lightValue = 0; /* data from sensor pin */
  
  delay( 50 );
  
  for( int index = 0; index < dataSize; index++ ) {
    /* reading data */
    lightValue = analogRead( sensorPin );
    Serial.println( lightValue );
    data[ index ] = lightValue;
    delay( 100 ); /* allow delay for more representative data sample */
  }
  
}

/***************************************************************************
% Routine Name : getAverage
% File :         Speedometer.ino
% Parameters:    data     -- an array of integer data
%                dataSize -- size of data array 
% Description :  Get the mean of the data set "data"
% Return:        The calculated average value in the data array
***************************************************************************/
double getAverage( int * data, int dataSize ) {
  long total = 0;      /* .sum of data element values */
  long lightValue = 0; /* new data element */
  
  for( int index = 0; index < dataSize; index++ ) {
    /* sum for total */
    total += data[ index ];
  }
  
  return total / dataSize;
}

/***************************************************************************
% Routine Name : getStanDev
% File :         Speedometer.ino
% Parameters:    data     -- set of data points 
%                dataSize -- size of data array
%                average  -- average value from the data set
% Description :  Calculates the standard deviation of the set of data
% Return:        Standard deviation of data
***************************************************************************/
double getStanDev( int * data, int dataSize, double average ) {
  long  deviations = 0; /* data point deviations */
    
  for( int index = 0; index < dataSize; index++ ) {
    /* treat all points equally */
    deviations += sq( data[index] - average );
  }

  /* unbiased sample size hence (dataSize - 1) */
  return sqrt( deviations / (dataSize - 1) ); 
}

