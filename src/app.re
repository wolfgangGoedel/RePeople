Wp.import "style/app.css";

module App = {
  include ReactRe.Component;
  type props = unit;
  let name = "App";
  let render _ =>
    <div className="App">
      <header> <AppBar /> </header>
      <main>
        <Card>
          <Card.Title
            main=(<a href="#">(ReactRe.stringToElement "Hello")</a>)
            sub=(ReactRe.stringToElement "Reason")
          />
        </Card>
      </main>
    </div>;
};

include ReactRe.CreateComponent App;

let createElement = wrapProps ();