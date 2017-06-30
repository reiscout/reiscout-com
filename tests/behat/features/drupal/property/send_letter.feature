Feature: Check send letter buttons appearance and functionality.
  Scenario: User who bought prop access can send send a letter if owner data filled in
    - no buttons when no owner info
    - when no points the button to buy points shown instead
    - the points are decreasing
    - only one letter available to send for one prop for one user