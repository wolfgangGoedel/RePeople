Wp.importUnit "style/card.css";

module Card = {
  include ReactRe.Component;
  type props = {title: string};
  let name = "Card";
  let render {props} =>
    <div className="Card card">
      <div className="card-content">
        <div className="card-title"> (ReactRe.stringToElement props.title) </div>
      </div>
    </div>;
};

include ReactRe.CreateComponent Card;

let createElement ::title => wrapProps {title: title};