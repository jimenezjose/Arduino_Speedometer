/****************************************************************************

                                                Jose Jorge Jimenez-Olivas
                                                July 27, 2018

                            Speedometer

File Name:       Speedometer.ino
Description:     With a white strip of paper, a photoresister, and an
                 LED, a speedometer can be easily implemented using 
                 statistical hypothesis testing with a significance level
                 of 0.1%.
****************************************************************************/
#define SAMPLE_SIZE 100
#define SIGNIFICANT_SCORE 3 /* p-value(x < 3) = 99% */
#define ONE_SECOND 1000     /* speedmoter respond time */

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
  double Z_Score = (currLight - average) / stanDev;
  
  if( reading && Z_Score > SIGNIFICANT_SCORE ) {
    /* 1 revolution noted */
    revolutions++;
    Serial.println( "White line marked" );
    Serial.print( "CurrLight: " );
    Serial.println( currLight );
    Serial.print( "Z Score: " );
    Serial.println( Z_Score );
    reading = false;
  }
  else if( !reading && Z_Score <= 0 ) {
    reading = true;
  }

  unsigned long currentMillis = millis();
  if( revolutions && currentMillis - previousMillis >= ONE_SECOND ) {
    /* revolutions per minute */
    double dt = (currentMillis - previousMillis);
    dt = dt * (1.0 / 1000) * ( 1.0 / 60);
    long rpm = revolutions / dt;
    //Serial.print( "revolutions: " );
    //Serial.println( revolutions );
    Serial.print( "rpm: " );
    Serial.println( rpm );
    previousMillis = currentMillis;
    revolutions = 0;
  } 

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

