WebPack.require("./appBar.css");

let logo = WebPack.requireImage("./appBar.logo.svg");

let component = ReasonReact.statelessComponent("AppBar");

let make = (~shown, ~onClick, _children) => {
  ...component,
  render: (_self) =>
    <nav className="AppBar">
      <img className="AppBar-logo" src=logo alt="People" />
      <hr />
      <a onClick> (ReasonReact.stringToElement(shown)) </a>
    </nav>
};