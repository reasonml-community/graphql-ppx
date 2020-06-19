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
module MyQuery = {
  [@ocaml.warning "-32"];
  module Raw = {
    type t_v1 = {
      .
      "nullableString": Js.Nullable.t(string),
      "string": Js.Nullable.t(string),
    };
    type t_v2 = {
      .
      "nullableString": Js.Nullable.t(string),
      "string": Js.Nullable.t(string),
    };
    type t = {
      .
      "v1": t_v1,
      "v2": t_v2,
    };
    type t_variables = {. "var": bool};
  };
  /**The GraphQL query string*/
  let query = "query ($var: Boolean!)  {\nv1: variousScalars  {\nnullableString @skip(if: $var) \nstring @skip(if: $var) \n}\n\nv2: variousScalars  {\nnullableString @include(if: $var) \nstring @include(if: $var) \n}\n\n}\n";
  type t_v1 = {
    .
    "nullableString": option(string),
    "string": option(string),
  };
  type t_v2 = {
    .
    "nullableString": option(string),
    "string": option(string),
  };
  type t = {
    .
    "v1": t_v1,
    "v2": t_v2,
  };
  type t_variables = {. "var": bool};
  /**Parse the JSON GraphQL data to ReasonML data types*/
  let parse = (value: Raw.t): t => {
    let v2 = {
      let value = value##v2;
      let string = {
        let value = value##string;
        switch (Js.toOption(value)) {
        | Some(value) => Some(value)
        | None => None
        };
      }
      and nullableString = {
        let value = value##nullableString;
        switch (Js.toOption(value)) {
        | Some(value) => Some(value)
        | None => None
        };
      };
      {"nullableString": nullableString, "string": string};
    }
    and v1 = {
      let value = value##v1;
      let string = {
        let value = value##string;
        switch (Js.toOption(value)) {
        | Some(value) => Some(value)
        | None => None
        };
      }
      and nullableString = {
        let value = value##nullableString;
        switch (Js.toOption(value)) {
        | Some(value) => Some(value)
        | None => None
        };
      };
      {"nullableString": nullableString, "string": string};
    };
    {"v1": v1, "v2": v2};
  };
  /**Serialize the ReasonML GraphQL data that was parsed using the parse function back to the original JSON compatible data */
  let serialize = (value: t): Raw.t => {
    let v2 = {
      let value = value##v2;
      let string = {
        let value = value##string;
        switch (value) {
        | Some(value) => Js.Nullable.return(value)
        | None => Js.Nullable.null
        };
      }
      and nullableString = {
        let value = value##nullableString;
        switch (value) {
        | Some(value) => Js.Nullable.return(value)
        | None => Js.Nullable.null
        };
      };
      {"nullableString": nullableString, "string": string};
    }
    and v1 = {
      let value = value##v1;
      let string = {
        let value = value##string;
        switch (value) {
        | Some(value) => Js.Nullable.return(value)
        | None => Js.Nullable.null
        };
      }
      and nullableString = {
        let value = value##nullableString;
        switch (value) {
        | Some(value) => Js.Nullable.return(value)
        | None => Js.Nullable.null
        };
      };
      {"nullableString": nullableString, "string": string};
    };
    {"v1": v1, "v2": v2};
  };
  let serializeVariables: t_variables => Raw.t_variables =
    inp => {"var": (a => a)(inp##var)};
  let makeVariables = (~var, ()) =>
    serializeVariables({"var": var}: t_variables);
  external unsafe_fromJson: Js.Json.t => Raw.t = "%identity";
  external toJson: Raw.t => Js.Json.t = "%identity";
  external variablesToJson: Raw.t_variables => Js.Json.t = "%identity";
  module Z__INTERNAL = {
    type root = t;
    type nonrec graphql_module;
    /****--- graphql-ppx module ---**

The contents of this module are automatically generated by `graphql-ppx`.
The following is simply an overview of the most important variables and types that you can access from this module.

```
module MyQuery {
  /**
  The GraphQL query string
  */
  let query: string;

  /**
  This is the main type of the result you will get back.
  You can hover above the identifier key (e.g. query or mutation) to see the fully generated type for your module.
  */
  type t;

  /**
  Parse the JSON GraphQL data to ReasonML data types
  */
  let parse: Raw.t => t;

  /**
  Serialize the ReasonML GraphQL data that was parsed using the parse function back to the original JSON compatible data
  */
  let serialize: t => Raw.t;

  /**
  This is the JSON compatible type of the GraphQL data.
  It should not be necessary to access the types inside for normal use cases.
  */
  module Raw: { type t; };
}
```*/
    let graphql_module: graphql_module = Obj.magic(0);
  };
};
