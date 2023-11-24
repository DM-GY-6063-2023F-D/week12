let SERIAL_PORT = "/dev/cu.usbmodem3485187B80BC2";

let mSerial;
let readyToReceive;
let cBackgroundColor;

function serialEvent() {
  let line = mSerial.readLine();
  trim(line);
  if (!line) return;

  if (line.charAt(0) != "{") {
    print("error: ", line);
    readyToReceive = true;
    return;
  }

  let data = JSON.parse(line).data;
  let a0 = data.A0;

  cBackgroundColor = map(a0.value, a0.min, a0.max, 0, 255);
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

  mSerial.openPort(SERIAL_PORT, { baudRate: 9600 });
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
