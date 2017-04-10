Wp.import "style/app.css";

open ReactRe;

module App = {
  include Component;
  type props = unit;
  let name = "App";
  let render _ => (
    <div className="App">
      <header> <AppBar /> </header>
      <main>
        <Card>
          <Card.Avatar photoUrl="" />
          <Card.Title
            main=(<a href="#">(stringToElement "Firstname Lastname")</a>)
            sub=(stringToElement "Entity")
          />
          <Card.Info icon="email">
            <a href="mailto:lastname@entity.com">(stringToElement "lastname@entity.com")</a>
          </Card.Info>
          <Card.Info icon="phone">
          </Card.Info>
          <Card.Info icon="supervisor_account" desc="manager">
          </Card.Info>
        </Card>
      </main>
    </div>
  );
};

include CreateComponent App;

let createElement = wrapProps ();