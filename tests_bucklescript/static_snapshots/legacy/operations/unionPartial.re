[@ocaml.ppx.context
  {
    tool_name: "migrate_driver",
    include_dirs: [],
    load_path: [],
    open_modules: [],
    for_package: None,
    debug: false,
    use_threads: false,
    use_vmthreads: false,
    recursive_types: false,
    principal: false,
    transparent_modules: false,
    unboxed_types: false,
    unsafe_string: false,
    cookies: [],
  }
];
module MyQuery' = {
  module Raw = {
    type t_dogOrHuman_Dog = {
      .
      "__typename": string,
      "name": string,
      "barkVolume": float,
    };
    type t_dogOrHuman;
    type t = {. "dogOrHuman": t_dogOrHuman};
    type t_variables = Js.Json.t;
  };
  let query = "query   {\ndogOrHuman  {\n__typename\n...on Dog   {\nname  \nbarkVolume  \n}\n\n}\n\n}\n";
  type t_dogOrHuman_Dog = {
    .
    "name": string,
    "barkVolume": float,
  };
  type t_dogOrHuman = [
    | `FutureAddedValue(Js.Json.t)
    | `Dog(t_dogOrHuman_Dog)
  ];
  type t = {. "dogOrHuman": t_dogOrHuman};
  type t_variables = Js.Json.t;
  let parse: Raw.t => t =
    value => {
      let dogOrHuman = {
        let value = value##dogOrHuman;
        let typename: string =
          Obj.magic(Js.Dict.unsafeGet(Obj.magic(value), "__typename"));
        (
          switch (typename) {
          | "Dog" =>
            `Dog(
              {
                let value: Raw.t_dogOrHuman_Dog = Obj.magic(value);
                let barkVolume = {
                  let value = value##barkVolume;
                  value;
                }
                and name = {
                  let value = value##name;
                  value;
                };
                {"name": name, "barkVolume": barkVolume};
              },
            )
          | _ => `FutureAddedValue(Obj.magic(value): Js.Json.t)
          }: t_dogOrHuman
        );
      };
      {"dogOrHuman": dogOrHuman};
    };
  let serialize: t => Raw.t =
    value => {
      let dogOrHuman = {
        let value = value##dogOrHuman;
        switch (value) {
        | `Dog(value) => (
            Obj.magic(
              {
                let barkVolume = {
                  let value = value##barkVolume;
                  value;
                }
                and name = {
                  let value = value##name;
                  value;
                };
                {"__typename": "Dog", "name": name, "barkVolume": barkVolume};
              },
            ): Raw.t_dogOrHuman
          )
        | `FutureAddedValue(value) => (Obj.magic(value): Raw.t_dogOrHuman)
        };
      };
      {"dogOrHuman": dogOrHuman};
    };
  let make = () => {
    "query": query,
    "variables": Js.Json.null,
    "parse": parse,
  };
  module Z__INTERNAL = {
    type root = t;
    type nonrec graphql_module;
    /****--- GraphQL PPX Module ---**

The contents of this module are automatically generated by `graphql-ppx`.
The following is simply an overview of the most important variables and types that you can access from this module.

```
module MyQuery {
  // This is the stringified representation of your query, which gets sent to the server.
  let query: string;

  // This is the main type of the result you will get back.
  // You can hover above the identifier key (e.g. query or mutation) to see the fully generated type for your module.
  type t;

  // This function turns your raw result from the server into the reason/ocaml representation of that result.
  // Depending on your graphql client library, this process should happen automatically for you.
  let parse: Raw.t => t;

  // This function will prepare your data for sending it back to the server.
  // Depending on your graphql client library, this process should happen automatically for you.
  let serialize: t => Raw.t;

  // The definition tuple is primarily used to interact with client libraries.
  // The types are equivalent to: (parse, query, serialize).
  // Your client library will use these values to provide the properly parsed / serialized data for you.
  let definition: (
    Raw.t => t,
    string,
    t => Raw.t
  );

  // This is the representation of your raw result coming from the server.
  // It should not be necessary to access the types inside for normal use cases.
  module Raw: { type t; };
}
```*/
    let graphql_module: graphql_module = Obj.magic(0);
  };
};
module MyQuery = {
  include MyQuery';
  module type query_type = (module type of MyQuery');
  let self: module query_type = (module MyQuery');
};
