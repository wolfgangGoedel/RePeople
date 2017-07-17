let component = ReasonReact.statelessComponent "ListAll";
let make people::people _children => {
  ...component,
  render: fun _self =>
    <div className="card-container">
      (ReasonReact.arrayToElement
        (Array.map 
          (fun person => <PersonCard person=person />)
          people
      ))
    </div>
};