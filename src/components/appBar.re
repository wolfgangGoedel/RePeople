Utils.import "style/appBar.css";

module AppBar = {
  include ReactRe.Component;
  type props = unit;
  let name = "AppBar";
  let logo = Utils.importString "assets/appBar.logo.svg";
  let render _ =>
    <nav className="AppBar">
      <img className="AppBar-logo" src=logo alt="People" />
    </nav>
    ;
};

include ReactRe.CreateComponent AppBar;

let createElement = wrapProps ();