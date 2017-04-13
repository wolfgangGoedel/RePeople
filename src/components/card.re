Wp.import "style/card.css";

open ReactRe;

module Card = {
  include Component;
  type props = {children: list reactElement};
  let name = "Card";
  let render {props} =>
    <div className="Card card">
      <div className="card-content"> (listToElement props.children) </div>
    </div>;
};

include CreateComponent Card;

let createElement ::children => wrapProps {children: children} ::children;

module Title = {
  type props = {main: reactElement, sub: reactElement};
  let render (props: props) =>
    <div className="card-title">
      <div> props.main </div>
      <div className="card-subtitle"> props.sub </div>
    </div>;
  let createElement ::main ::sub=nullElement => ReactPlus.withDefault render {main, sub};
};

module Avatar = {
  type props = {photoUrl: string, altText: string};
  let render {photoUrl, altText} => <img className="card-avatar" src=photoUrl alt=altText />;
  let createElement ::photoUrl ::altText="" => ReactPlus.withDefault render {photoUrl, altText};
};

module Info = {
  type props = {icon: string, desc: string, children: list reactElement};
  let render {icon, desc, children} =>
    <div className="card-info">
      <i className="material-icons" title=desc> (stringToElement icon) </i>
      <span> (listToElement children) </span>
    </div>;
  let createElement ::icon ::desc=icon ::children => ReactPlus.withDefault render {icon, desc, children} ::children;
};