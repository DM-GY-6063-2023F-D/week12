let readyToLoad;
let cBackgroundColor;

function setup() {
  createCanvas(windowWidth, windowHeight);
  readyToLoad = true;
  cBackgroundColor = 0;
}

function draw() {
  background(cBackgroundColor);

  if (readyToLoad) {
    readyToLoad = false;
    loadJSON("http://10.10.81.101/A0", parseA0);
  }
}

function parseA0(res) {
  let a0Val = res.data.A0;
  readyToLoad = true;
  cBackgroundColor = map(a0Val, 0, 4095, 0, 255);
}
