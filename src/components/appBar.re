Utils.import "style/appBar.css";

let logo = Utils.importString "assets/appBar.logo.svg";

let component = ReasonReact.statelessComponent "AppBar";
let make shown::shown onClick::onClick _children => {
  ...component,
  render: fun _self => {
    <nav className="AppBar">
      <img className="AppBar-logo" src=logo alt="People" />
      <hr />
      <a onClick=onClick> (ReasonReact.stringToElement shown) </a>
    </nav>
  }
};
