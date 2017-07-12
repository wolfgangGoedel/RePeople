Utils.import "style/card.css";

let component = ReasonReact.statelessComponent "Card";
let make children => {
  ...component,
  render: fun _self =>
    <div className="Card card">
      (ReasonReact.createDomElement "div" props::{"className":"card-content"} children)
    </div>
};

module Title = {
  let component = ReasonReact.statelessComponent "Title";
  let make main::main sub::sub _children => {
    ...component,
    render: fun _self =>
      <div className="card-title">
        <div> main </div>
        <div className="card-subtitle"> sub </div>
      </div>
  };
};

module Avatar = {
  let component = ReasonReact.statelessComponent "Avatar";
  let make photoUrl::photoUrl altText::altText="altText" _children => {
    ...component,
    render: fun _self =>
      <img className="card-avatar" src=photoUrl alt=altText />
  };
};

module Info = {
  let component = ReasonReact.statelessComponent "Info";
  let make icon::icon desc::desc="" children => {
    ...component,
    render: fun _self => {
      <div className="card-info">
        <i className="material-icons" title=desc> (ReasonReact.stringToElement icon) </i>
        (ReasonReact.createDomElement "span" props::{"className":""} children)
      </div>
    }
  };
};
