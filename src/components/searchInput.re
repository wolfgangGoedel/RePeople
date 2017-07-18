Utils.import "style/searchInput.css";

let component = ReasonReact.statelessComponent "SearchInput";
let make id::id label::label value::value onChange::onChange _children => {
  {
    ...component,
    render: fun _self => {
      <div className="SearchInput input-field">
        <i className="material-icons prefix"> (ReasonReact.stringToElement "search") </i>
        <input id=id _type="text" value=value onChange=onChange />
        <label htmlFor=id> (ReasonReact.stringToElement label) </label>
      </div>
    }
  };
};
