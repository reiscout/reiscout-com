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