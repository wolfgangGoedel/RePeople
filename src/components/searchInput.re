WebPack.require("./searchInput.css");

let component = ReasonReact.statelessComponent("SearchInput");

let make = (~id, ~label, ~value, ~onChange, _children) => {
  ...component,
  render: (_self) =>
    <div className="SearchInput input-field">
      <i className="material-icons prefix"> (ReasonReact.stringToElement("search")) </i>
      <input id _type="text" value onChange />
      <label htmlFor=id> (ReasonReact.stringToElement(label)) </label>
    </div>
};
