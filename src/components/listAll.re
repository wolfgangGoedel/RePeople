type state = {
  filterPattern: string
};

let component = ReasonReact.statefulComponent "ListAll";
let make people::(people:Model.people) _children => {
  let updateFilterPattern _state filterPattern =>
    {filterPattern: filterPattern};
  let filterPatternUpdater filterPattern {ReasonReact.state: state} =>
    ReasonReact.Update (updateFilterPattern state filterPattern);

  let onSearchInputChange self event =>
    self.ReasonReact.update filterPatternUpdater ((ReactDOMRe.domElementToObj (ReactEventRe.Form.target event))##value);

  let rec matchPatternOnValues pattern (values:list string) => {
    let patternLength = String.length pattern;
    switch values {
    | [h, ...r] => switch (patternLength <= (String.length h) && pattern === (String.sub h 0 patternLength |> String.lowercase) || pattern === "") {
                  | true => true
                  | false => matchPatternOnValues pattern r
                  }
    | [] => false
    };
  };

  {
    ...component,
    initialState: fun () => {filterPattern: ""},
    render: fun self => {
      let {filterPattern} = self.state;

      <div>
        <div className="card-container">
          (ReasonReact.arrayToElement
            (people
              |> Array.fold_left (fun acc (person:Model.person) => {
                  switch (matchPatternOnValues (String.lowercase filterPattern) [person.firstname, person.lastname, person.entity, person.phone, person.manager |> Utils.unwrap]) {
                  | true => Array.append acc [|person|]
                  | false => acc
                  };
                }) [||]
              |> Array.map (fun person => <PersonCard person=person />)
            )
          )
        </div>
        <div className="control-container">
          <SearchInput id="searchInput" label="Search" value=filterPattern onChange=(onSearchInputChange self) />
        </div>
      </div>
    }
  };
};
