Feature: Check GET APP LINK VIA SMS block on homepage.
  Scenario: Fill in the block.
    Given I am in the "/" path
    And I fill in "Phone number" with "+79003264403"
    And I press "GetLink"
    Then I should see "Message has been sent on your number, it may take a few minutes until you receive it."