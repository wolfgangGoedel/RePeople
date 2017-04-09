module App = {
  include ReactRe.Component;
  type props = unit;
  let name = "App";
  let render _ => <div className="App"> <header /> <main /> </div>;
};

include ReactRe.CreateComponent App;

let createElement = wrapProps ();