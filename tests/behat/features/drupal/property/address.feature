Feature: Check address features.
  Scenario: Check user do not see wnah do not have to see on property which not bought.
    Given I logged in as 'picture_buyer'
    And I go to "property/472" page
    Then I should see  "Buy Property Address for " on page
    And I should not see "1376 Athens Avenue Southwest" in "Address"
    And I should not see "1376 Athens Avenue Southwest" in "Owner Address"
    And I should not see "Send a letter to Proprty Owner"
    And I should not see "Buy Owner Info"
    And I should not see "Buy Points to send letters"
    And I should not see "Buy Points to buy owner info"

  Scenario: User see address and owner info after buy property access
    Given I logged in as 'picture_buyer'
    And I go to "property/467" page
    Then I should see  "Buy Property Address for " on page
    Then I press "Buy Property Address for " button
    Then I should see message "Address Access for Property #467 added to your cart."
    And I go to "/cart"
    Then I should see "Address Access for Property #467"
    And I press "Checkout"
    Then I fill Billing Information
    And press "Continue to next step"
    Then I should see "Review order"
    And I fill in CC info
    And press "Continue to next step"
    Then I should see "Checkout Complete"
    Then I go to "/purchased-property-address"
    And should see "1600 Pennsylvania Avenue, McDonough, GA, United States"
    # After property bought Investor can see owner info and address
    Then I go to "property/467" page
    And I should see "1600 Pennsylvania Ave"
    And I should see "Owner Address"
    # Investor can not edit the node.
    And I should not see "edit"