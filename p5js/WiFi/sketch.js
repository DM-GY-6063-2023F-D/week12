let readyToLoad;
let cBackgroundColor;

function parseData(res) {
  let data = res.data;
  let a0Val = data.A0;
  readyToLoad = true;
  cBackgroundColor = map(a0Val, 0, 4095, 0, 255);
}

function setup() {
  createCanvas(windowWidth, windowHeight);
  readyToLoad = true;
  cBackgroundColor = 0;
}

function draw() {
  background(cBackgroundColor);

  if (readyToLoad) {
    readyToLoad = false;
    loadJSON("http://10.10.81.101/data", parseData);
  }
}
