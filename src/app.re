Wp.importUnit "style/app.css";

module App = {
  include ReactRe.Component;
  type props = unit;
  let name = "App";
  let render _ =>
    <div className="App">
      <header> <AppBar /> </header>
      <main> <Card title="Hello Reason" /> </main>
    </div>;
};

include ReactRe.CreateComponent App;

let createElement = wrapProps ();