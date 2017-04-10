Wp.importUnit "style/card.css";

module Card = {
  include ReactRe.Component;
  type props = {children: list ReactRe.reactElement};
  let name = "Card";
  let render {props} =>
    <div className="Card card">
      <div className="card-content">
        <div className="card-title"> (ReactRe.listToElement props.children) </div>
      </div>
    </div>;
};

include ReactRe.CreateComponent Card;

let createElement ::children => wrapProps {children: children} ::children;

module Title = {
  type props = {main: ReactRe.reactElement, sub: option ReactRe.reactElement};
  let render (props: props) =>
    <div className="card-title">
      <div> props.main </div>
      <div className="card-subtitle">
        (
          switch props.sub {
          | Some sub => sub
          | None => ReactRe.nullElement
          }
        )
      </div>
    </div>;
  let createElement ::main ::sub=? children::_ () => render {main, sub};
};