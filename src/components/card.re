Wp.import "style/card.css";

open ReactRe;

module Card = {
  include Component;
  type props = {children: list reactElement};
  let name = "Card";
  let render {props} =>
    <div className="Card card">
      <div className="card-content">
        (listToElement props.children)
      </div>
    </div>;
};

include CreateComponent Card;

let createElement ::children => wrapProps {children: children} ::children;

module Title = {
  type props = {main: reactElement, sub: reactElement};
  let render (props: props) =>
    <div className="card-title">
      <div> props.main </div>
      <div className="card-subtitle">
        props.sub
      </div>
    </div>;
  let createElement ::main ::sub=nullElement children::_ () => render {main, sub};
};

module Avatar = {
  let createElement ::photoUrl ::altText="" children::_ () =>
    <img className="card-avatar" src=photoUrl alt=altText />;
};

module Info = {
  let createElement ::icon ::desc=icon ::children () => {
    <div className="card-info">
      <i className="material-icons" title=desc>
        (stringToElement icon)
      </i>
      <span>
        (listToElement children)
      </span>
    </div>    
  }
};