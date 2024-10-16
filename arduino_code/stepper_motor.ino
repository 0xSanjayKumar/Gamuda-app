const int stepPin = 5;
const int dirPin = 2;
const int enPin = 8;

//stepper motor setting

int max_speed = 200;
int stop_count = 0;
int point_stop_time = 1000;
int steps_array[] = {1000, 2000, 3000}; 
int num_stop_points = sizeof(steps_array) / sizeof(steps_array[0]); 
int current_location;

// stops define
const int pointA = 10;
const int pointB = 11; 
const int pointC = 12; 


void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  
  pinMode(pointA, INPUT);
  pinMode(pointB, INPUT);
  pinMode(pointC, INPUT);

  Serial.begin(9600);
}

void loop() {

  if (stop_count == 0) {
    delay(5000);
  }
  
  if (stop_count >= 1 && stop_count <= num_stop_points) {
    digitalWrite(dirPin, HIGH); 
    forward(steps_array[stop_count - 1]); 
    current_location = steps_array[stop_count-1];
    stop();
  }
  else if (stop_count > num_stop_points && stop_count <= 2 * num_stop_points) {
    digitalWrite(dirPin, LOW); 
    backward(steps_array[(2 * num_stop_points) - stop_count]);
    stop();
  }

  if (digitalRead(pointA) == 1){
    int reach_point = current_location - steps_array[stop_count-1]; //have to update this
    backward(reach_point);
  }
  else  if (digitalRead(pointB) == 1){
  }
  else  if (digitalRead(pointC) == 1){
    stop_count = 3;
  }
    Serial.println(stop_count);  
  delay(1000);
  stop_count = stop_count + 1;
}

void forward(int step_count) {
  for (int count = 0; count <= step_count; count++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(max_speed); 
    digitalWrite(stepPin, LOW);
    delayMicroseconds(max_speed); 
  }
}

void backward(int step_count) {
  for (int count = 0; count <= step_count; count++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(max_speed); 
    digitalWrite(stepPin, LOW);
    delayMicroseconds(max_speed); 
  }
}

void stop() {
  digitalWrite(enPin, HIGH); 
  delay(point_stop_time);
  digitalWrite(enPin, LOW); 
}
