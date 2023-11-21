let mSerial;
let readyToReceive;
let cBackgroundColor;

function serialEvent() {
  let currentString = mSerial.readLine();
  trim(currentString);
  if (!currentString) return;

  let data = JSON.parse(currentString).data;
  let a0Val = data.A0;

  cBackgroundColor = map(a0Val, 0, 4095, 0, 255);
  readyToReceive = true;
}

function serialError(err) {
  print("Something went wrong with the serial port", err);
}

function setup() {
  createCanvas(windowWidth, windowHeight);
  cBackgroundColor = 0;

  mSerial = new p5.SerialPort();

  mSerial.on("data", serialEvent);
  mSerial.on("error", serialError);

  mSerial.openPort("/dev/cu.usbmodem3485187B80BC2", { baudRate: 9600 });
  mSerial.clear();
  readyToReceive = true;
}

function draw() {
  background(cBackgroundColor);

  if (readyToReceive) {
    mSerial.clear();
    mSerial.write(0xAB);
    readyToReceive = false;
  }
}
