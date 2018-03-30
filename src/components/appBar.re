WebPack.require("./appBar.css");

let logo = WebPack.requireImage("./appBar.logo.svg");

let component = ReasonReact.statelessComponent("AppBar");

let make = _children => {
  ...component,
  render: _self =>
    <nav className="AppBar">
      <img className="AppBar-logo" src=logo alt="People" />
      <hr className="grow" />
      <a onClick=((_) => ReasonReact.Router.push("/discover"))>
        (ReasonReact.stringToElement("discover"))
      </a>
      <hr />
      <a onClick=((_) => ReasonReact.Router.push("/all"))>
        (ReasonReact.stringToElement("show all"))
      </a>
    </nav>
};